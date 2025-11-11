#set has_constructor = False
#if 'constructor' in $current_class.methods
#set has_constructor = True
${current_class.methods.constructor.generate_code($current_class)}
#end if
#
#set generator = $current_class.generator
#set methods = $current_class.methods_clean()
#set st_methods = $current_class.static_methods_clean()
#

static void js_register_${generator.prefix}_${current_class.class_name}(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    #if $current_class.is_ref_class or $current_class.has_constructor
    v8pp::class_<${current_class.namespaced_class_name}> class_${current_class.class_name}(isolate);
    #else
    v8pp::class_<${current_class.namespaced_class_name}> class_${current_class.class_name}(isolate, [](v8::Isolate*,const auto&){/* No constructor class will not be destroyed by script */});
    #end if

    class_${current_class.class_name}

    #if has_constructor
        .ctor(
        #set impls = []
        #if $current_class.methods.constructor.is_overloaded
            #set impls = $current_class.methods.constructor.implementations
        #else
            #set impls = [$current_class.methods.constructor]
        #end if
        #set $impl_count = False
        #for fn in $impls
            #set $current_arg_count = $fn.min_args
            #while $current_arg_count <= len($fn.arguments)
                #set typed_arg_array = []
                #set arg_array = []
                #set $index = 0
                #for arg in $fn.arguments
                    #if $index < $current_arg_count
                        #set $arg_name = "arg" + str(index)
                        #set $index = $index + 1
                        #set $typed_arg_array += [$arg.to_string($generator) + " " + $arg_name]
                        #set $arg_array += [$arg_name]
                    #end if
                #end for
                #set typed_arg_list = ", ".join($typed_arg_array)
                #set arg_list = ", ".join($arg_array)
            #set $impl_count = $impl_count + 1
            #if $impl_count > 1
            ,
            #end if
        [](${typed_arg_list}) {
            return new ${current_class.namespaced_class_name}(${arg_list});
        }
            #set $current_arg_count = $current_arg_count + 1
            #end while
        #end for
        )
    #end if

    #if len($current_class.parents) > 0
    .template inherit<${current_class.parents[0].namespaced_class_name}>()
    #end if

    #for m in methods
        .member_function("${m['name']}"
        #set fn = m['impl']
        #set impls = []
        #set direct_bind = False
        #if $fn.is_overloaded
            #set impls = $fn.implementations
        #else
            #set impls = [$fn]
            #set direct_bind = $fn.min_args == len($fn.arguments)
        #end if

        #if $direct_bind
            , &${current_class.namespaced_class_name}::${fn.func_name}
        #else

        #for fn in $impls
            #set $current_arg_count = $fn.min_args
            #while $current_arg_count <= len($fn.arguments)
                #set typed_arg_array = [$current_class.namespaced_class_name + "* self"]
                #set arg_array = []
                #set $index = 0
                #for arg in $fn.arguments
                    #if $index < $current_arg_count
                        #set $arg_name = "arg" + str(index)
                        #set $index = $index + 1
                        #set $typed_arg_array += [$arg.to_string($generator) + " " + $arg_name]
                        #set $arg_array += [$arg_name]
                    #end if
                #end for
                #set typed_arg_list = ", ".join($typed_arg_array)
                #set arg_list = ", ".join($arg_array)
        , [](${typed_arg_list}) {
            #if str($fn.ret_type) == 'void'
            self->${fn.func_name}(${arg_list});
            #else
            return self->${fn.func_name}(${arg_list});
            #end if
        }
            #set $current_arg_count = $current_arg_count + 1
            #end while
        #end for

        #end if
        )
    #end for

    #for m in st_methods
        .static_function("${m['name']}"
        #set fn = m['impl']
        #set impls = []
        #set direct_bind = 0
        #if $fn.is_overloaded
            #set impls = $fn.implementations
        #else
            #set impls = [$fn]
            #set direct_bind = $fn.min_args == len($fn.arguments)
        #end if

        #if $direct_bind
            , &${current_class.namespaced_class_name}::${fn.func_name}
        #else

        #for fn in $impls
            #set $current_arg_count = $fn.min_args
            #while $current_arg_count <= len($fn.arguments)
                #set typed_arg_array = []
                #set arg_array = []
                #set $index = 0
                #for arg in $fn.arguments
                    #if $index < $current_arg_count
                        #set $arg_name = "arg" + str(index)
                        #set $index = $index + 1
                        #set $typed_arg_array += [$arg.to_string($generator) + " " + $arg_name]
                        #set $arg_array += [$arg_name]
                    #end if
                #end for
                #set typed_arg_list = ", ".join($typed_arg_array)
                #set arg_list = ", ".join($arg_array)
        , [](${typed_arg_list}) {
            #if str($fn.ret_type) == 'void'
            ${current_class.namespaced_class_name}::${fn.func_name}(${arg_list});
            #else
            return ${current_class.namespaced_class_name}::${fn.func_name}(${arg_list});
            #end if
        }
            #set $current_arg_count = $current_arg_count + 1
            #end while
        #end for

        #end if
        )
    #end for

    .auto_wrap_objects(true);

    mod.class_("${current_class.class_name}", class_${current_class.class_name});
}
