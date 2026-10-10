#include "pending_operator_common.h"

#include <string>
#include <vector>

#include "operator_common.h"

#include "f8cppengine/constants.h"
#include "f8cppsdk/runtime_node_registry.h"

namespace f8::cppengine {

using f8::cppsdk::RuntimeNodeRegistry;

json pending_operator_spec(const std::string& operator_class, const std::string& label, const std::string& category,
                           const std::vector<json>& data_in, const std::vector<json>& data_out,
                           const std::vector<json>& states, const std::vector<std::string>& exec_in,
                           const std::vector<std::string>& exec_out, const json& edit_policy) {
  json spec{{"specKind", "operator"},
            {"schemaVersion", "f8operator/1"},
            {"serviceClass", kServiceClass},
            {"paletteCategory", std::string(kServiceClass) + "." + category},
            {"operatorClass", operator_class},
            {"version", "0.0.1"},
            {"label", label},
            {"description", label + " operator described for C++ engine graphs. Native runtime is pending."},
            {"hiddenInPalette", true},
            {"tags", json::array({"cpp", "pending"})}};
  if (!exec_in.empty()) {
    spec["execInPorts"] = json::array();
    for (const auto& name : exec_in) spec["execInPorts"].push_back(json{{"name", name}});
  }
  if (!exec_out.empty()) {
    spec["execOutPorts"] = json::array();
    for (const auto& name : exec_out) spec["execOutPorts"].push_back(json{{"name", name}});
  }
  if (!data_in.empty()) spec["dataInPorts"] = data_in;
  if (!data_out.empty()) spec["dataOutPorts"] = data_out;
  if (!states.empty()) spec["stateFields"] = states;
  if (!edit_policy.is_null()) spec["editPolicy"] = edit_policy;
  return spec;
}

void register_pending_operator_spec(RuntimeNodeRegistry& registry, const json& spec) {
  const std::string operator_class = spec.value("operatorClass", "");
  if (operator_class.empty()) return;
  registry.register_operator_spec(spec, true);
}

}  // namespace f8::cppengine
