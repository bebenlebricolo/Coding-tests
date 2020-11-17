#include "node.h"


int main()
{
    Node avrgcc("avrgcc");
    Node common("common", avrgcc);
    Node Device("Device", common);
    Device.value = "-mmcu=atmega328p";

    Node outputfiles("outputfiles", common);
    Node hex("hex", outputfiles);
    hex.value = true;
    Node lss("lss", outputfiles);
    lss.value = true;
    Node eep("eep", outputfiles);
    eep.value = true;
    Node srec("srec", outputfiles);
    srec.value = true;
    Node usersignature("usersignature", outputfiles);
    usersignature.value = true;

    outputfiles.add_child(hex);
    outputfiles.add_child(lss);
    outputfiles.add_child(eep);
    outputfiles.add_child(srec);
    outputfiles.add_child(usersignature);
    common.add_child(outputfiles);
    common.add_child(Device);
    avrgcc.add_child(common);



    return 0;
}