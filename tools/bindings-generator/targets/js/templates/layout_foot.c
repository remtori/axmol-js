void js_register_all_${prefix}(JsRegistry& registry)
{
	#if $target_ns
	v8pp::module& mod = registry.module("${target_ns}");
	#else
	v8pp::module& mod = registry.module("__TODO__");
	#end if

	#for jsclass in $sorted_classes
		#if $in_listed_classes(jsclass)
	js_register_${prefix}_${jsclass}(mod);
		#end if
	#end for
}

#if $macro_judgement
\#endif
#end if
