//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2003 Ahmet Sekercioglu
// Copyright (C) 2003-2015 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

class UE: public cSimpleModule {
protected:
    // The following redefined virtual function holds the algorithm.
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

class RAN: public cSimpleModule {
protected:
    // The following redefined virtual function holds the algorithm.
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

class AMF: public cSimpleModule {
protected:
    // The following redefined virtual function holds the algorithm.
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

class AUSF: public cSimpleModule {
protected:
    // The following redefined virtual function holds the algorithm.
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

class SMF: public cSimpleModule {
protected:
    // The following redefined virtual function holds the algorithm.
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

class PCF: public cSimpleModule {
protected:
    // The following redefined virtual function holds the algorithm.
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

class UDM: public cSimpleModule {
protected:
    // The following redefined virtual function holds the algorithm.
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

// The module class needs to be registered with OMNeT++
Define_Module(UE);
Define_Module(RAN);
Define_Module(AMF);
Define_Module(AUSF);
Define_Module(PCF);
Define_Module(SMF);
Define_Module(UDM);

void UE::initialize() {

    cMessage *msg = new cMessage("registration_request"); //Registration procedure - step 1
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
    if (strcmp("registration_request", msg->getName()) == 0) {
        cMessage *msg = new cMessage("registration_request"); //Registration procedure - step 3
        send(msg, "out_amf");
    }
}

void AMF::initialize() {

}

void AMF::handleMessage(cMessage *msg) {
    if (strcmp("registration_request", msg->getName()) == 0) {
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
    } else if (strcmp("Auth-Resp",
            msg->getName()) == 0) {
        cMessage *msg = new cMessage("Nausf_UEAuthentication_Authenticate_Request_Challenge"); //Authentication procedure for EAP-AKA' - step 7
        send(msg, "out_ausf");
    } else if (strcmp("Nausf_UEAuthentication_Authenticate_Response",
            msg->getName()) == 0) {
        cMessage *msg = new cMessage("EAP-SUCCESS"); //Authentication procedure for EAP-AKA' - step 11
        send(msg, "out_ue");
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
    } else if (strcmp("Nausf_UEAuthentication_Authenticate_Request_Challenge", msg->getName())
            == 0) {
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
    }
}
