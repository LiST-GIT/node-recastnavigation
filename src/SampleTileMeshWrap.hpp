#ifndef SampleTileMeshWrap_hpp
#define SampleTileMeshWrap_hpp

#include <node.h>
#include <nan.h>
#include <Sample.h>
#include <Sample_TileMesh.h>
#include <SampleInterfaces.h>
#include <DetourNavMeshQuery.h>
#include <InputGeom.h>

using namespace v8;

class SampleTileMeshWrap : public Nan::ObjectWrap, Sample_TileMesh {
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

    void saveAll(const char* path, const dtNavMesh* mesh) {
        Sample::saveAll(path, mesh);
    }
    dtNavMesh* loadAll(const char* path) {
        return Sample::loadAll(path);
    };
};

#endif