#ifndef SampleSoloMeshWrap_hpp
#define SampleSoloMeshWrap_hpp

#include <node.h>
#include <nan.h>
#include <Sample.h>
#include <Sample_SoloMesh.h>
#include <SampleInterfaces.h>
#include <DetourNavMeshQuery.h>
#include <InputGeom.h>

using namespace v8;

class SampleSoloMeshWrap : public Nan::ObjectWrap, Sample_SoloMesh {
private:
public:
    static Nan::Persistent<v8::FunctionTemplate> constructor;

    static NAN_MODULE_INIT(Init);
    static NAN_METHOD(New);
    static NAN_METHOD(Load);
    static NAN_METHOD(AddOffMeshConnection);
    static NAN_METHOD(DeleteOffMeshConnection);
    static NAN_METHOD(GetOffMeshConnectionCount);
    static NAN_METHOD(Build);
    static NAN_METHOD(FindPath);
    static NAN_METHOD(FindNearestPoly);
};

#endif