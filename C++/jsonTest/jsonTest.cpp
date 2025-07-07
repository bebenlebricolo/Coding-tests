#include <rapidjson/prettywriter.h>
#include <rapidjson/document.h>

#include <cmath>
#include <fstream>

using namespace rapidjson;
int main()
{
    StringBuffer buffer;
    PrettyWriter<StringBuffer> writer(buffer);

    writer.StartObject();
    writer.Key("Key1");
    writer.String("Value1");

    writer.Key("NewObject");
    writer.StartObject();
    writer.Key("Name");
    writer.String("Inner object");

    writer.Key("Age");
    writer.Uint(34);

    writer.Key("X");
    writer.Double(-0.256);
    writer.Key("Y");
    writer.Double(0.145);
    writer.Key("Z");
    writer.Double(33.256);

    writer.Key("Data");
    writer.StartArray();

    for (uint8_t i = 0 ;  i < 15 ; i++)
    {
        double num = (15.12 * pow(-0.325, i) * cos(pow(-0.325, i))) ;
        writer.Double(num);
    }
    writer.EndArray();

    // End of inner object
    writer.EndObject();

    // End of root object
    writer.EndObject();

    std::ofstream outfile("test.json", std::ofstream::out);
    outfile << buffer.GetString();

    return 0;
}