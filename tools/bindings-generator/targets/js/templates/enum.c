
#set fields = $current_class.fields

static int js_register_${generator.prefix}_${current_class.class_name}(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::module module_${current_class.class_name}(isolate);
    module_${current_class.class_name}
    #for m in fields
    .const_("${m['name']}", ${m['value']})
    #end for
    ;

    mod.submodule("${current_class.class_name}", module_${current_class.class_name});
    return 1;
}
