#include "drl_gui_module.hpp"
#include "drl_gui_signal.hpp"
#include <concepts>
#include <tuple>
#include <type_traits>


#ifndef DRL_GUI_TYPE
#define DRL_GUI_TYPE

namespace drl
{
    using module_tuple_type = std::tuple<drl::button_module,
                                         drl::input_box_module,
                                         drl::output_box_module>;
    template <unsigned t>
    using module_type = typename std::tuple_element<t, module_tuple_type>::type;
} // namespace drl



#endif