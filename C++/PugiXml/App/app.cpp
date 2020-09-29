#include <string>
#include <iostream>

#include "pugixml.hpp"

void append_inlined_node_child_pcdata(pugi::xml_node& parent, const std::string& node_name, const std::string& value = "")
{
    pugi::xml_node node = parent.append_child(node_name.c_str());
    if (0 != value.size())
    {
        pugi::xml_node child = node.append_child(pugi::node_pcdata);
        child.set_value(value.c_str());
    }
}

void build_simulator_configuration(pugi::xml_node& parent, const std::string& device_signature = "0x1E930B", const std::string& stimuli_filepath = "")
{
    append_inlined_node_child_pcdata(parent, "avrtool", "com.atmel.avrdbg.tool.simulator");
    append_inlined_node_child_pcdata(parent, "avrtoolserialnumber");
    append_inlined_node_child_pcdata(parent, "avrdeviceexpectedsignature", device_signature.c_str());
    pugi::xml_node simulator_configuration_node = parent.append_child("com_atmel_avrdbg_tool_simulator");
    pugi::xml_node tool_options_node = simulator_configuration_node.append_child("ToolOptions");
    append_inlined_node_child_pcdata(tool_options_node, "InterfaceProperties");
    append_inlined_node_child_pcdata(tool_options_node, "InterfaceName");

    append_inlined_node_child_pcdata(simulator_configuration_node, "ToolType", "com.atmel.avrdbg.tool.simulator");
    append_inlined_node_child_pcdata(simulator_configuration_node, "ToolNumber");
    append_inlined_node_child_pcdata(simulator_configuration_node, "ToolName", "Simulator");

    if(!stimuli_filepath.empty())
    {
        append_inlined_node_child_pcdata(parent, "StimuliFile", stimuli_filepath.c_str());
    }
    append_inlined_node_child_pcdata(parent, "avrtoolinterface");
}

void build_device_prop_group(pugi::xml_node& parent, const std::string& target_name)
{
    // @see http://www.gerald-fahrnholz.eu/sw/DocGenerated/HowToUse/html/group___grp_pugi_xml.html#pugi_xml_generated_file
    pugi::xml_node property_group = parent.append_child("PropertyGroup");
    append_inlined_node_child_pcdata(property_group, "SchemaVersion", "2.0");
    append_inlined_node_child_pcdata(property_group, "ProjectVersion", "7.0");
    append_inlined_node_child_pcdata(property_group, "ToolchainName", "com.Atmel.AVRGCC8.C");
    append_inlined_node_child_pcdata(property_group, "ProjectGuid", "dce6c7e3-ee26-4d79-826b-08594b9ad897");
    append_inlined_node_child_pcdata(property_group, "avrdevice", "ATmega328P");
    append_inlined_node_child_pcdata(property_group, "avrdeviceseries", "none");
    append_inlined_node_child_pcdata(property_group, "OutputType", "Executable");
    append_inlined_node_child_pcdata(property_group, "Language", "C");
    append_inlined_node_child_pcdata(property_group, "OutputFileName", "$(MSBuildProjectName)");
    append_inlined_node_child_pcdata(property_group, "OutputFileExtension", ".elf");
    append_inlined_node_child_pcdata(property_group, "OutputDirectory", "$(MSBuildProjectDirectory)\\$(Configuration)");
    append_inlined_node_child_pcdata(property_group, "AssemblyName", target_name);
    append_inlined_node_child_pcdata(property_group, "Name", target_name);
    append_inlined_node_child_pcdata(property_group, "RootNamespace", target_name);
    append_inlined_node_child_pcdata(property_group, "ToolchainFlavour", "Native");
    append_inlined_node_child_pcdata(property_group, "KeepTimersRunning", "true");
    append_inlined_node_child_pcdata(property_group, "OverrideVtor", "false");
    append_inlined_node_child_pcdata(property_group, "CacheFlash", "true");
    append_inlined_node_child_pcdata(property_group, "ProgFlashFromRam", "true");
    append_inlined_node_child_pcdata(property_group, "RamSnippetAddress");
    append_inlined_node_child_pcdata(property_group, "UncachedRange");
    append_inlined_node_child_pcdata(property_group, "preserveEEPROM", "true");
    append_inlined_node_child_pcdata(property_group, "OverrideVtorValue");
    append_inlined_node_child_pcdata(property_group, "BootSegment", "2");
    append_inlined_node_child_pcdata(property_group, "ResetRule", "0");
    append_inlined_node_child_pcdata(property_group, "eraseonlaunchrule", "0");
    append_inlined_node_child_pcdata(property_group, "EraseKey");

    pugi::xml_node asf_framework_config = property_group.append_child("AsfFrameworkConfig");
    pugi::xml_node framework_data_node = asf_framework_config.append_child("framework-data");
    framework_data_node.append_attribute("xmlns").set_value("");
    append_inlined_node_child_pcdata(framework_data_node, "options");
    append_inlined_node_child_pcdata(framework_data_node, "configurations");
    append_inlined_node_child_pcdata(framework_data_node, "files");

    pugi::xml_node documentation_node = framework_data_node.append_child("documentation");
    documentation_node.append_attribute("help").set_value("");
    pugi::xml_node offline_documentation_node = framework_data_node.append_child("offline-documentation");
    offline_documentation_node.append_attribute("help").set_value("");

    pugi::xml_node dependencies_node = framework_data_node.append_child("dependencies");
    pugi::xml_node content_extension_node = dependencies_node.append_child("content-extension");
    content_extension_node.append_attribute("eid").set_value("atmel.asf");
    content_extension_node.append_attribute("uuidref").set_value("Atmel.ASF");
    content_extension_node.append_attribute("version").set_value("3.40.0");

    build_simulator_configuration(property_group);
}

void build_configuration_xml_group(pugi::xml_node& parent, const std::string& build_type)
{
    pugi::xml_node property_group_node = parent.append_child("PropertyGroup");
    std::string conditionnal_str = " '$(Configuration)' == '" + build_type + "' ";
    property_group_node.append_attribute("Condition").set_value(conditionnal_str.c_str());

    pugi::xml_node toolchain_settings_node = property_group_node.append_child("ToolchainSettings");
    pugi::xml_node avr_gcc_node = toolchain_settings_node.append_child("AvrGcc");

    append_inlined_node_child_pcdata(avr_gcc_node, "avrgcc.common.Device", "-mmcu=atmega328p -B \"%24(PackRepoDir)\\atmel\\ATmega_DFP\\1.2.209\\gcc\\dev\\atmega328p\"");
    append_inlined_node_child_pcdata(avr_gcc_node, "avrgcc.common.outputfiles.hex", "True");
    append_inlined_node_child_pcdata(avr_gcc_node, "avrgcc.common.outputfiles.lss", "True");
    append_inlined_node_child_pcdata(avr_gcc_node, "avrgcc.common.outputfiles.eep", "True");
    append_inlined_node_child_pcdata(avr_gcc_node, "avrgcc.common.outputfiles.srec", "True");
    append_inlined_node_child_pcdata(avr_gcc_node, "avrgcc.common.outputfiles.usersignatures", "False");
    append_inlined_node_child_pcdata(avr_gcc_node, "avrgcc.compiler.general.ChangeDefaultCharTypeUnsigned", "True");
    append_inlined_node_child_pcdata(avr_gcc_node, "avrgcc.compiler.general.ChangeDefaultBitFieldUnsigned", "True");

    // Preprocessor definitions
    pugi::xml_node avr_gcc_defsymbols_node = avr_gcc_node.append_child("avrgcc.compiler.symbols.DefSymbols");
    pugi::xml_node list_values_node = avr_gcc_defsymbols_node.append_child("ListValues");
    append_inlined_node_child_pcdata(list_values_node, "Value", "NDEBUG");

    // include directories
    pugi::xml_node include_directories_node = avr_gcc_node.append_child("avrgcc.compiler.directories.IncludePaths");
    list_values_node = include_directories_node.append_child("ListValues");
    append_inlined_node_child_pcdata(list_values_node, "Value", "%24(PackRepoDir)\\atmel\\ATmega_DFP\\1.2.209\\include");

    // Optimizations
    append_inlined_node_child_pcdata(avr_gcc_node, "avrgcc.compiler.optimization.level", "Optimize for size (-Os)");
    append_inlined_node_child_pcdata(avr_gcc_node, "avrgcc.compiler.optimization.PackStructureMembers", "True");
    append_inlined_node_child_pcdata(avr_gcc_node, "avrgcc.compiler.optimization.AllocateBytesNeededForEnum", "True");
    append_inlined_node_child_pcdata(avr_gcc_node, "avrgcc.compiler.warnings.AllWarnings", "True");

    // Configure linker link libraries
    pugi::xml_node linker_libraries_node = avr_gcc_node.append_child("avrgcc.linker.libraries.Libraries");
    list_values_node = linker_libraries_node.append_child("ListValues");
    append_inlined_node_child_pcdata(list_values_node, "Value", "libm");

    // Assembler include directories
    pugi::xml_node assembler_includes_node = avr_gcc_node.append_child("avrgcc.assembler.general.IncludePaths");
    list_values_node = assembler_includes_node.append_child("ListValues");
    append_inlined_node_child_pcdata(list_values_node, "Value", "%24(PackRepoDir)\\atmel\\ATmega_DFP\\1.2.209\\include");
}

void build_compile_item_group(pugi::xml_node& parent)
{
    pugi::xml_node item_group_node = parent.append_child("ItemGroup");
    pugi::xml_node compile_node = item_group_node.append_child("Compile");
    compile_node.append_attribute("Include") = "main.c";
    append_inlined_node_child_pcdata(compile_node, "SubType", "compile");
}

int main(int argc, char** argv)
{
    pugi::xml_document doc;
    // Prepend delcaration node will look like this : <?xml version="1.0" encoding="utf-8"?>
    pugi::xml_node decl = doc.prepend_child(pugi::node_declaration);
    decl.append_attribute("version") = "1.0";
    decl.append_attribute("encoding") = "utf-8";

    pugi::xml_node project_node = doc.append_child(pugi::node_element);
    project_node.set_name("Project");
    project_node.append_attribute("DefaultTargets") = "Build";
    project_node.append_attribute("xmlns") = "http://schemas.microsoft.com/developer/msbuild/2003";
    project_node.append_attribute("ToolsVersion") = "14.0";

    build_device_prop_group(project_node, "GenericApplication");
    build_configuration_xml_group(project_node, "Release");
    build_configuration_xml_group(project_node, "Debug");

    // Compile item group which lists sources to be built as part of this target
    build_compile_item_group(project_node);

    // Last node is dedicated to atmelstudio specific targets
    pugi::xml_node import_projects_node = project_node.append_child("Import");
    import_projects_node.append_attribute("Project") = R"($(AVRSTUDIO_EXE_PATH)\\Vs\\Compiler.targets)";

    doc.save_file("./output.xml", "  ");
    return 0;
}