#include <string>
#include <iostream>

#include "pugixml.hpp"

void append_inlined_node_child_pcdata(pugi::xml_node& parent, const std::string& node_name, const std::string& value)
{
	pugi::xml_node node = parent.append_child(node_name.c_str());
	pugi::xml_node child = node.append_child(pugi::node_pcdata);
	child.set_value(value.c_str());
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
	append_inlined_node_child_pcdata(property_group, "preserveEEPROM", "true");
	append_inlined_node_child_pcdata(property_group, "BootSegment", "2");
	append_inlined_node_child_pcdata(property_group, "ResetRule", "0");
	append_inlined_node_child_pcdata(property_group, "eraseonlaunchrule", "0");
	append_inlined_node_child_pcdata(property_group, "BootSegment", "2");

}

int main(int argc, char** argv)
{
	pugi::xml_document doc;
	// Prepend delcaration node will look like this : <?xml version="1.0" encoding="utf-8"?>
	pugi::xml_node decl = doc.prepend_child(pugi::node_declaration);
	decl.append_attribute("version") = "1.0";
	decl.append_attribute("encoding") = "UTF-8";

	pugi::xml_node project_node = doc.append_child(pugi::node_element);
	project_node.set_name("Project");
	project_node.append_attribute("DefaultTargets") = "Build";
	project_node.append_attribute("xmlns") = "http://schemas.microsoft.com/developer/msbuild/2003";
	project_node.append_attribute("ToolsVersion") = "14.0";

	build_device_prop_group(project_node, "GenericApplication");

	doc.save_file("./output.xml", "  ");
	return 0;
}