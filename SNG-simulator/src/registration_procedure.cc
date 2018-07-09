//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2003 Ahmet Sekercioglu
#include "registration_procedure.h"


void UE::initialize() {

    msg_registration_request *msg = new msg_registration_request("registration_request");  //Registration procedure - step 1
    msg->setExtended_protocol_discriminator(0x00);
    msg->setMessage_type(0x42);
    msg->setFGS_registration_type(0x01);
    msg->setNgKSI(0x00);
    msg->setFGS_mobile_identity(0x42);

    send(msg, "out_ran");
}

void UE::handleMessage(cMessage *msg) {
    if (strcmp("identity_request", msg->getName()) == 0) {
        cMessage *msg = new cMessage("identity_response"); //Registration procedure - step 7
        send(msg, "out_amf");
    } else if (strcmp("Auth-Req", msg->getName()) == 0) {
        cMessage *msg = new cMessage("Auth-Resp"); //Authentication procedure for EAP-AKA' - step 6
        send(msg, "out_amf");
    }
}

void RAN::initialize() {

}

void RAN::handleMessage(cMessage *msg) {
    msg_registration_request *msg2 = (msg_registration_request *) msg;
    if (msg2->getMessage_type() == 0x42) {
        send(msg2, "out_amf"); //Registration procedure - step 3
    }
}

void AMF::initialize() {

}

void AMF::handleMessage(cMessage *msg) {
    try{
        msg_registration_request *msg2 = (msg_registration_request *) msg;
    } catch(Exception e){

    }
    if (msg2->getMessage_type() == 0x42) {
        cMessage *msg = new cMessage("identity_request"); //Registration procedure - step 6
        send(msg, "out_ue");
    } else if (strcmp("identity_response", msg->getName()) == 0) {

        cMessage *msg = new cMessage(
                "Nausf_UEAuthentication_Authenticate_Request"); //Authentication procedure for EAP-AKA' - step 0
        send(msg, "out_ausf");
    } else if (strcmp("Nausf_UEAuthentication_Authenticate_Response_Challenge",
            msg->getName()) == 0) {
        cMessage *msg = new cMessage("Auth-Req"); //Authentication procedure for EAP-AKA' - step 4
        send(msg, "out_ue");
    } else if (strcmp("Auth-Resp", msg->getName()) == 0) {
        cMessage *msg = new cMessage(
                "Nausf_UEAuthentication_Authenticate_Request_Challenge"); //Authentication procedure for EAP-AKA' - step 7
        send(msg, "out_ausf");
    } else if (strcmp("Nausf_UEAuthentication_Authenticate_Response",
            msg->getName()) == 0) {
        cMessage *msg = new cMessage("EAP-SUCCESS"); //Authentication procedure for EAP-AKA' - step 11
        send(msg, "out_ue");

        cMessage *msg2 = new cMessage("Nudm_UECM_Registration"); //Registration procedure - step 14a
        send(msg2, "out_udm");
    } else if (strcmp("Nudm_UECM_Registration_Response",
            msg->getName()) == 0) {

        cMessage *msg = new cMessage("Nudm_SDM_Get"); //Registration procedure - step 14b
        send(msg, "out_udm");
    } else if (strcmp("Nudm_SDM_Get_Response",
            msg->getName()) == 0) {

        cMessage *msg = new cMessage("Nudm_SDM_Subscribe"); //Registration procedure - step 14c
        send(msg, "out_udm");
    }

}

void SMF::initialize() {

}

void SMF::handleMessage(cMessage *msg) {

}

void AUSF::initialize() {

}

void AUSF::handleMessage(cMessage *msg) {
    if (strcmp("Nausf_UEAuthentication_Authenticate_Request", msg->getName())
            == 0) {
        cMessage *msg = new cMessage("Nudm_UEAuthentication_Get_Request"); //Authentication procedure for EAP-AKA' - step 0
        send(msg, "out_udm");
    } else if (strcmp("Nudm_UEAuthentication_Get_Response", msg->getName())
            == 0) {
        cMessage *msg = new cMessage(
                "Nausf_UEAuthentication_Authenticate_Response_Challenge"); //Authentication procedure for EAP-AKA' - step 3
        send(msg, "out_amf");
    } else if (strcmp("Nausf_UEAuthentication_Authenticate_Request_Challenge",
            msg->getName()) == 0) {
        cMessage *msg = new cMessage(
                "Nausf_UEAuthentication_Authenticate_Response"); //Authentication procedure for EAP-AKA' - step 10
        send(msg, "out_amf");
    }

}

void PCF::initialize() {

}

void PCF::handleMessage(cMessage *msg) {

}

void UDM::initialize() {

}

void UDM::handleMessage(cMessage *msg) {
    if (strcmp("Nudm_UEAuthentication_Get_Request", msg->getName()) == 0) {
        cMessage *msg = new cMessage("Nudm_UEAuthentication_Get_Response"); //Authentication procedure for EAP-AKA' - step 2
        send(msg, "out_ausf");
    } else if (strcmp("Nudm_UECM_Registration", msg->getName())
            == 0) {
        cMessage *msg = new cMessage("Nudm_UECM_Registration_Response"); //Registration procedure - step 14a Response
        send(msg, "out_amf");
    } else if (strcmp("Nudm_SDM_Get", msg->getName())
            == 0) {
        cMessage *msg = new cMessage("Nudm_SDM_Get_Response"); //Registration procedure - step 14b Response
        send(msg, "out_amf");
    } else if (strcmp("Nudm_SDM_Subscribe", msg->getName())
            == 0) {
        cMessage *msg = new cMessage("Nudm_SDM_Subscribe_Response"); //Registration procedure - step 14c Response
        send(msg, "out_amf");
    }
}
