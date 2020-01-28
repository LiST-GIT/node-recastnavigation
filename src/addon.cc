#include <node.h>
#include <nan.h>

#include "SampleSoloMeshWrap.hpp"
#include "SampleTileMeshWrap.hpp"
#include "SampleTempObstaclesWrap.hpp"

using namespace v8;

void Init(Handle<Object> exports) {
    Nan::Set(exports, Nan::New("SAMPLE_POLYAREA_GROUND").ToLocalChecked(), Nan::New(SAMPLE_POLYAREA_GROUND));
    Nan::Set(exports, Nan::New("SAMPLE_POLYAREA_WATER").ToLocalChecked(), Nan::New(SAMPLE_POLYAREA_WATER));
    Nan::Set(exports, Nan::New("SAMPLE_POLYAREA_ROAD").ToLocalChecked(), Nan::New(SAMPLE_POLYAREA_ROAD));
    Nan::Set(exports, Nan::New("SAMPLE_POLYAREA_DOOR").ToLocalChecked(), Nan::New(SAMPLE_POLYAREA_DOOR));
    Nan::Set(exports, Nan::New("SAMPLE_POLYAREA_GRASS").ToLocalChecked(), Nan::New(SAMPLE_POLYAREA_GRASS));
    Nan::Set(exports, Nan::New("SAMPLE_POLYAREA_JUMP").ToLocalChecked(), Nan::New(SAMPLE_POLYAREA_JUMP));

    Nan::Set(exports, Nan::New("SAMPLE_POLYFLAGS_WALK").ToLocalChecked(), Nan::New(SAMPLE_POLYFLAGS_WALK));
    Nan::Set(exports, Nan::New("SAMPLE_POLYFLAGS_SWIM").ToLocalChecked(), Nan::New(SAMPLE_POLYFLAGS_SWIM));
    Nan::Set(exports, Nan::New("SAMPLE_POLYFLAGS_DOOR").ToLocalChecked(), Nan::New(SAMPLE_POLYFLAGS_DOOR));
    Nan::Set(exports, Nan::New("SAMPLE_POLYFLAGS_JUMP").ToLocalChecked(), Nan::New(SAMPLE_POLYFLAGS_JUMP));
    Nan::Set(exports, Nan::New("SAMPLE_POLYFLAGS_DISABLED").ToLocalChecked(), Nan::New(SAMPLE_POLYFLAGS_DISABLED));
    Nan::Set(exports, Nan::New("SAMPLE_POLYFLAGS_ALL").ToLocalChecked(), Nan::New(SAMPLE_POLYFLAGS_ALL));
    
    Nan::Set(exports, Nan::New("DT_STRAIGHTPATH_START").ToLocalChecked(), Nan::New(DT_STRAIGHTPATH_START));
    Nan::Set(exports, Nan::New("DT_STRAIGHTPATH_END").ToLocalChecked(), Nan::New(DT_STRAIGHTPATH_END));
    Nan::Set(exports, Nan::New("DT_STRAIGHTPATH_OFFMESH_CONNECTION").ToLocalChecked(), Nan::New(DT_STRAIGHTPATH_OFFMESH_CONNECTION));
    
    SampleSoloMeshWrap::Init(exports);
    SampleTileMeshWrap::Init(exports);
    SampleTempObstaclesWrap::Init(exports);
}

NODE_MODULE(addon, Init)
