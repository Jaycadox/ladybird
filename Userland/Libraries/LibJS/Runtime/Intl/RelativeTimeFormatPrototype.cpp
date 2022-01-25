/*
 * Copyright (c) 2022, Tim Flynn <trflynn89@pm.me>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibJS/Runtime/GlobalObject.h>
#include <LibJS/Runtime/Intl/RelativeTimeFormatPrototype.h>

namespace JS::Intl {

// 17.4 Properties of the Intl.RelativeTimeFormat Prototype Object, https://tc39.es/ecma402/#sec-properties-of-intl-relativetimeformat-prototype-object
RelativeTimeFormatPrototype::RelativeTimeFormatPrototype(GlobalObject& global_object)
    : PrototypeObject(*global_object.object_prototype())
{
}

void RelativeTimeFormatPrototype::initialize(GlobalObject& global_object)
{
    Object::initialize(global_object);

    auto& vm = this->vm();

    // 17.4.2 Intl.RelativeTimeFormat.prototype[ @@toStringTag ], https://tc39.es/ecma402/#sec-Intl.RelativeTimeFormat.prototype-toStringTag
    define_direct_property(*vm.well_known_symbol_to_string_tag(), js_string(vm, "Intl.RelativeTimeFormat"sv), Attribute::Configurable);

    u8 attr = Attribute::Writable | Attribute::Configurable;
    define_native_function(vm.names.resolvedOptions, resolved_options, 0, attr);
}

// 17.4.5 Intl.RelativeTimeFormat.prototype.resolvedOptions ( ), https://tc39.es/ecma402/#sec-intl.relativetimeformat.prototype.resolvedoptions
JS_DEFINE_NATIVE_FUNCTION(RelativeTimeFormatPrototype::resolved_options)
{
    // 1. Let relativeTimeFormat be the this value.
    // 2. Perform ? RequireInternalSlot(relativeTimeFormat, [[InitializedRelativeTimeFormat]]).
    auto* relative_time_format = TRY(typed_this_object(global_object));

    // 3. Let options be ! OrdinaryObjectCreate(%Object.prototype%).
    auto* options = Object::create(global_object, global_object.object_prototype());

    // 4. For each row of Table 15, except the header row, in table order, do
    //     a. Let p be the Property value of the current row.
    //     b. Let v be the value of relativeTimeFormat's internal slot whose name is the Internal Slot value of the current row.
    //     c. Assert: v is not undefined.
    //     d. Perform ! CreateDataPropertyOrThrow(options, p, v).
    MUST(options->create_data_property_or_throw(vm.names.locale, js_string(vm, relative_time_format->locale())));
    MUST(options->create_data_property_or_throw(vm.names.style, js_string(vm, relative_time_format->style_string())));
    MUST(options->create_data_property_or_throw(vm.names.numeric, js_string(vm, relative_time_format->numeric_string())));
    MUST(options->create_data_property_or_throw(vm.names.numberingSystem, js_string(vm, relative_time_format->numbering_system())));

    // 5. Return options.
    return options;
}

}
