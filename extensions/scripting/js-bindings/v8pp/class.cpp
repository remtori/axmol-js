#include "v8pp/class.hpp"

#include <cassert>
#include <cstdio>  // for snprintf

#include "axmol/base/Logging.h"
#include "js-bindings/manual/JSEngine.h"

namespace v8pp::detail
{

static V8PP_IMPL std::string pointer_str(void const* ptr)
{
    std::string buf(sizeof(void*) * 2 + 3, 0);  // +3 for 0x and \0 terminator
    int const len =
#if defined(_MSC_VER) && (_MSC_VER < 1900)
        sprintf_s(&buf[0], buf.size(), "%p", ptr);
#else
        snprintf(&buf[0], buf.size(), "%p", ptr);
#endif
    buf.resize(len < 0 ? 0 : len);
    return buf;
}

/////////////////////////////////////////////////////////////////////////////
//
// class_info
//
V8PP_IMPL class_info::class_info(type_info const& type) : type(type) {}

V8PP_IMPL std::string class_info::class_name() const
{
    return "v8pp::class_<" + std::string(type.name()) + ">";
}

/////////////////////////////////////////////////////////////////////////////
//
// object_registry
//
V8PP_IMPL object_registry::object_registry(v8::Isolate* isolate, type_info const& type, dtor_function&& dtor)
    : class_info(type)
    , isolate_(isolate)
    , ctor_()  // no wrapped class constructor available by default
    , dtor_(std::move(dtor))
    , auto_wrap_objects_(false)
    , only_reference_objects_(false)
{
    v8::HandleScope scope(isolate_);

    v8::Local<v8::FunctionTemplate> js_func =
        v8::FunctionTemplate::New(isolate_, [](v8::FunctionCallbackInfo<v8::Value> const& args) {
        v8::Isolate* isolate = args.GetIsolate();
        v8::HandleScope scope(isolate);

        object_registry* this_ = external_data::get<object_registry*>(args.Data());
        try
        {
            v8::Local<v8::Object> wrapped;
            {
                v8::TryCatch try_catch(isolate);
                wrapped = this_->wrap_object(args);
                if (try_catch.HasCaught())
                {
                    args.GetReturnValue().Set(try_catch.ReThrow());
                    return;
                }
            }

            if (wrapped.IsEmpty())
            {
                args.GetReturnValue().Set(throw_ex(isolate, "Failed to constructor native object"));
            }
            else
            {
                auto* engine = ax::JSEngine::fromIsolate(isolate);

                v8::Local<v8::Context> context = isolate->GetCurrentContext();

                // If we have a NewTarget (JavaScript class extending native class),
                // fix the prototype chain to maintain JavaScript inheritance
                if (!args.NewTarget().IsEmpty() && args.NewTarget()->IsFunction())
                {
                    v8::Local<v8::Function> newTarget = args.NewTarget().As<v8::Function>();
                    v8::Local<v8::Value> prototype;
                    if (newTarget->Get(context, engine->ext().prototype()).ToLocal(&prototype) && prototype->IsObject())
                    {
                        wrapped->SetPrototype(context, prototype).Check();
                    }
                }

                v8::Local<v8::Value> ctor;
                if (wrapped->Get(context, engine->ext()._ctor()).ToLocal(&ctor) && ctor->IsFunction())
                {
                    std::vector<v8::Local<v8::Value>> argv;
                    argv.reserve(args.Length());
                    for (int i = 0; i < args.Length(); i++)
                    {
                        argv.push_back(args[i]);
                    }

                    (void)ctor.As<v8::Function>()->Call(context, wrapped, argv.size(), argv.data());
                }

                args.GetReturnValue().Set(wrapped);
            }
        }
        catch (std::exception const& ex)
        {
            args.GetReturnValue().Set(throw_ex(isolate, ex.what()));
        }
    }, external_data::set(isolate, this));

    js_func_.Reset(isolate, js_func);

    // each JavaScript instance has 2 internal fields:
    //  0 - pointer to a wrapped C++ object
    //  1 - pointer to this object_registry
    js_func->InstanceTemplate()->SetInternalFieldCount(2);
}

V8PP_IMPL object_registry::~object_registry()
{
    remove_objects();
}

V8PP_IMPL void object_registry::set_ctor(ctor_function&& ctor)
{
    ctor_ = std::move(ctor);
    if (!ctor_)
    {
        return;
    }
}

V8PP_IMPL void object_registry::set_base(object_registry& info, cast_function cast)
{
    if (base_.has_value())
    {
        // assert(false && "duplicated inheritance");
        throw std::runtime_error(class_name() + " is already inherited from " + base_->info.class_name());
    }

    base_.emplace(info, cast);
    info.derivatives_.emplace_back(this);
}

V8PP_IMPL bool object_registry::cast(pointer_type& ptr, type_info const& actual_type) const
{
    if (this->type == actual_type || !ptr)
    {
        return true;
    }

    // fast way - search a direct parent
    if (base_.has_value() && base_->info.type == actual_type)
    {
        ptr = base_->cast(ptr);
        return true;
    }

    // slower way - walk on hierarhy
    if (base_.has_value())
    {
        pointer_type p = base_->cast(ptr);
        if (base_->info.cast(p, actual_type))
        {
            ptr = p;
            return true;
        }
    }

    return false;
}

V8PP_IMPL void object_registry::remove_object(object_id const& obj)
{
    auto it = objects_.find(static_cast<pointer_type>(obj));
    // assert(it != objects_.end() && "no object");
    if (it != objects_.end())
    {
        v8::HandleScope scope(isolate_);
        reset_object(it->first, it->second);
        objects_.erase(it);
    }
}

V8PP_IMPL void object_registry::remove_objects()
{
    v8::HandleScope scope(isolate_);
    for (auto& object_wrapped : objects_)
    {
        reset_object(object_wrapped.first, object_wrapped.second);
    }
    objects_.clear();
}

V8PP_IMPL typename object_registry::pointer_type object_registry::find_object(object_id id,
                                                                              type_info const& actual_type) const
{
    auto it = objects_.find(static_cast<pointer_type>(id));
    if (it != objects_.end())
    {
        pointer_type ptr = it->first;
        // TODO: Integrate type info like Godot into AXMOL
        // if (cast(ptr, actual_type))
        {
            return ptr;
        }
    }
    return nullptr;
}

V8PP_IMPL v8::Local<v8::Object> object_registry::find_v8_object(pointer_type const& ptr) const
{
    auto it = objects_.find(ptr);
    if (it != objects_.end())
    {
        return to_local(isolate_, it->second.pobj);
    }

    v8::Local<v8::Object> result;
    for (auto const info : derivatives_)
    {
        result = info->find_v8_object(ptr);
        if (!result.IsEmpty())
            break;
    }
    return result;
}

V8PP_IMPL v8::Local<v8::Object> object_registry::wrap_object(pointer_type const& object, size_t size)
{
    if (!object)
    {
        return {};
    }

    auto it = objects_.find(object);
    if (it != objects_.end())
    {
        // assert(false && "duplicate object");
        throw std::runtime_error(class_name() + " duplicate object " + pointer_str(static_cast<object_id>(object)));
    }

    v8::EscapableHandleScope scope(isolate_);

    // AXLOGI("Ctor call from C++");
    v8::Local<v8::Context> context = isolate_->GetCurrentContext();
    v8::Local<v8::Object> obj;
    if (js_function_template()->InstanceTemplate()->NewInstance(context).ToLocal(&obj))
    {
        obj->SetAlignedPointerInInternalField(0, static_cast<object_id>(object));
        obj->SetAlignedPointerInInternalField(1, this);

        v8::Global<v8::Object> pobj(isolate_, obj);
        pobj.SetWeak(this, [](v8::WeakCallbackInfo<object_registry> const& data) {
            object_id object       = data.GetInternalField(0);
            object_registry* this_ = static_cast<object_registry*>(data.GetInternalField(1));
            this_->remove_object(object);
        }, v8::WeakCallbackType::kInternalFields);
        objects_.emplace(object, wrapped_object{std::move(pobj), size});
        // AXLOGI("Wrap object {} -> {}", type.name(), object);
        if (size)
        {
            increase_allocated_memory(size);
        }
    }

    return scope.Escape(obj);
}

V8PP_IMPL v8::Local<v8::Object> object_registry::wrap_object(v8::FunctionCallbackInfo<v8::Value> const& args)
{
    if (!ctor_)
    {
        // assert(false && "create not allowed");
        throw std::runtime_error(class_name() + " has no constructor");
    }
    auto [object, size] = ctor_(args);
    return wrap_object(object, size);
}

V8PP_IMPL typename object_registry::pointer_type object_registry::unwrap_object(v8::Local<v8::Value> value)
{
    v8::HandleScope scope(isolate_);
    // AXLOGI("> Try unwrap object");

    while (value->IsObject())
    {
        v8::Local<v8::Object> obj = value.As<v8::Object>();

        // AXLOGI(">>>> Try {}", v8pp::from_v8<std::string>(isolate_, obj->GetConstructorName()));
        if (obj->InternalFieldCount() == 2)
        {
            object_id id = obj->GetAlignedPointerFromInternalField(0);
            if (id)
            {
                auto registry = static_cast<object_registry*>(obj->GetAlignedPointerFromInternalField(1));
                if (registry)
                {
                    pointer_type ptr = registry->find_object(id, type);
                    if (ptr)
                    {
                        // AXLOGI("> Unwrap object {} success", id);
                        return ptr;
                    }
                }
            }
        }
#if V8_MAJOR_VERSION > 12 || (V8_MAJOR_VERSION == 12 && V8_MINOR_VERSION >= 9)
        value = obj->GetPrototypeV2();
#else
        value = obj->GetPrototype();
#endif
    }

    // AXLOGI("> Unwrap object failed");
    return nullptr;
}

V8PP_IMPL void object_registry::reset_object(pointer_type const& object, wrapped_object& wrapped)
{
    if (wrapped.size)
    {
        decrease_allocated_memory(wrapped.size);
        dtor_(isolate_, object);
    }
    wrapped.pobj.Reset();
}

/////////////////////////////////////////////////////////////////////////////
//
// classes
//
V8PP_IMPL object_registry& classes::add(v8::Isolate* isolate,
                                        type_info const& type,
                                        typename object_registry::dtor_function&& dtor)
{
    classes* info = instance(operation::add, isolate);
    auto it       = info->find(type);
    if (it != info->classes_.end())
    {
        // assert(false && "class already registred");
        throw std::runtime_error((*it)->class_name() + " is already exist in isolate " + pointer_str(isolate));
    }
    info->classes_.emplace_back(new object_registry(isolate, type, std::move(dtor)));
    return *static_cast<object_registry*>(info->classes_.back().get());
}

V8PP_IMPL void classes::remove(v8::Isolate* isolate, type_info const& type)
{
    classes* info = instance(operation::get, isolate);
    if (info)
    {
        auto it = info->find(type);
        if (it != info->classes_.end())
        {
            info->classes_.erase(it);
            if (info->classes_.empty())
            {
                instance(operation::remove, isolate);
            }
        }
    }
}

V8PP_IMPL object_registry& classes::find(v8::Isolate* isolate, type_info const& base_type, type_info const& actual_type)
{
    classes* info = instance(operation::get, isolate);
    if (info)
    {
        auto it = info->find(actual_type);
        if (it != info->classes_.end())
        {
            return *static_cast<object_registry*>(it->get());
        }

        it = info->find(base_type);
        if (it != info->classes_.end())
        {
            return *static_cast<object_registry*>(it->get());
        }
    }

    throw std::runtime_error(class_info(actual_type).class_name() + " extends " + class_info(base_type).class_name() +
                             " is not registered in isolate " + pointer_str(isolate));
}

V8PP_IMPL object_registry& classes::find(v8::Isolate* isolate, type_info const& type)
{
    classes* info = instance(operation::get, isolate);
    if (info)
    {
        auto it = info->find(type);
        if (it != info->classes_.end())
        {
            return *static_cast<object_registry*>(it->get());
        }
    }

    throw std::runtime_error(class_info(type).class_name() + " is not registered in isolate " + pointer_str(isolate));
}

V8PP_IMPL void classes::remove_all(v8::Isolate* isolate)
{
    instance(operation::remove, isolate);
}

V8PP_IMPL classes::classes_info::iterator classes::find(type_info const& type)
{
    return std::find_if(classes_.begin(), classes_.end(),
                        [&type](classes_info::value_type const& info) { return info->type == type; });
}

V8PP_IMPL classes* classes::instance(operation op, v8::Isolate* isolate)
{
#if defined(V8PP_ISOLATE_DATA_SLOT)
    classes* info = static_cast<classes*>(isolate->GetData(V8PP_ISOLATE_DATA_SLOT));
    switch (op)
    {
    case operation::get:
        return info;
    case operation::add:
        if (!info)
        {
            info = new classes;
            isolate->SetData(V8PP_ISOLATE_DATA_SLOT, info);
        }
        return info;
    case operation::remove:
        if (info)
        {
            delete info;
            isolate->SetData(V8PP_ISOLATE_DATA_SLOT, nullptr);
        }
        return nullptr;
    }
#else
    static std::unordered_map<v8::Isolate*, classes> instances;
    switch (op)
    {
    case operation::get:
    {
        auto it = instances.find(isolate);
        return it != instances.end() ? &it->second : nullptr;
    }
    case operation::add:
        return &instances[isolate];
    case operation::remove:
        instances.erase(isolate);
        return nullptr;
    }
#endif
    return nullptr;  // should never reach this line
}

}  // namespace v8pp::detail

namespace v8pp
{

V8PP_IMPL void cleanup(v8::Isolate* isolate)
{
    detail::classes::remove_all(isolate);
    detail::external_data::destroy_all(isolate);
}

}  // namespace v8pp
