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

// The module class needs to be registered with OMNeT++
Define_Module(UE);
Define_Module(RAN);
Define_Module(AMF);

void UE::initialize() {

    cMessage *msg = new cMessage("registration_request");
    send(msg, "out1");
}

void UE::handleMessage(cMessage *msg) {
    if (strcmp("identity_request", msg->getName()) == 0) {

        //cMessage *msg = new cMessage("registration_request");
        //send(msg, "out1", 0);
    }
}

void RAN::initialize() {

}

void RAN::handleMessage(cMessage *msg) {
    if (strcmp("registration_request", msg->getName()) == 0) {
        cMessage *msg = new cMessage("registration_request");
        send(msg, "out2");
    }
    else if (strcmp("identity_request", msg->getName()) == 0) {
        cMessage *msg = new cMessage("identity_request");
        send(msg, "out1");
    }
}

void AMF::initialize() {

}

void AMF::handleMessage(cMessage *msg) {
    if (strcmp("registration_request", msg->getName()) == 0) {
        cMessage *msg = new cMessage("identity_request");
        send(msg, "out1");
    }
}
