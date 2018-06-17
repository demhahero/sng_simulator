simple UE
{
    gates:
        input in_amf;
        input in_ran;
        output out_amf;
        output out_ran;
}

//
// TODO documentation
//
simple RAN
{
    gates:
        input in_ue;
        input in_amf;
        output out_ue;
        output out_amf;
}

//
// TODO documentation
//
simple AMF
{
    gates:
        input in_ue;
        input in_smf;
        input in_ausf;
        input in_pcf;
        input in_ran;
        input in_udm;
        output out_ue;
        output out_smf;
        output out_ausf;
        output out_pcf;
        output out_ran;
        output out_udm;
}

simple PCF
{
    gates:
        input in_smf;
        input in_amf;
        output out_smf;
        output out_amf;
}

//
// TODO documentation
//
simple UDM
{
    gates:
        input in_ausf;
        input in_amf;
        input in_smf;
        output out_smf;
        output out_amf;
        output out_ausf;
}

simple SMF
{
    gates:
        input in_amf;
        input in_udm;
        input in_pcf;
        output out_amf;
        output out_udm;
        output out_pcf;
}

simple AUSF
{
    gates:
        input in_amf;
        input in_udm;
        output out_amf;
        output out_udm;
}

//
// TODO documentation
//
network Network
{
    @display("bgb=808,363");
    submodules:
        UE_1: UE {
            @display("p=64,221");
        }
        RAN_1: RAN {
            @display("p=172,221");
        }
        AMF_1: AMF {
            @display("p=172,128");
        }
        AUSF_1: AUSF {
            @display("p=254,40");
        }
        PCF_1: PCF {
            @display("p=390,128");
        }
        UDM_1: UDM {
            @display("p=390,40");
        }
        SMF_1: SMF {
            @display("p=281,167");
        }
    connections:
        UE_1.out_ran --> RAN_1.in_ue;
        UE_1.out_amf --> AMF_1.in_ue;

        RAN_1.out_ue --> UE_1.in_ran;
        RAN_1.out_amf --> AMF_1.in_ran;

        AMF_1.out_ue --> UE_1.in_amf;
        AMF_1.out_ran --> RAN_1.in_amf;
        AMF_1.out_ausf --> AUSF_1.in_amf;
        AMF_1.out_udm --> UDM_1.in_amf;
        AMF_1.out_smf --> SMF_1.in_amf;
        AMF_1.out_pcf --> PCF_1.in_amf;

        AUSF_1.out_amf --> AMF_1.in_ausf;
        AUSF_1.out_udm --> UDM_1.in_ausf;

        SMF_1.out_amf --> AMF_1.in_smf;
        SMF_1.out_udm --> UDM_1.in_smf;
        SMF_1.out_pcf --> PCF_1.in_smf;

        PCF_1.out_amf --> AMF_1.in_pcf;
        PCF_1.out_smf --> SMF_1.in_pcf;

        UDM_1.out_amf --> AMF_1.in_udm;
        UDM_1.out_ausf --> AUSF_1.in_udm;
        UDM_1.out_smf --> SMF_1.in_udm;

}

