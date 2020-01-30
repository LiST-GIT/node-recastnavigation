#include <node.h>
#include <nan.h>

#include "SampleSoloMeshWrap.hpp"
#include "SampleTileMeshWrap.hpp"
#include "SampleTempObstaclesWrap.hpp"

using namespace v8;

NAN_MODULE_INIT(Init) {
    Nan::Set(target, Nan::New("SAMPLE_POLYAREA_GROUND").ToLocalChecked(), Nan::New(SAMPLE_POLYAREA_GROUND));
    Nan::Set(target, Nan::New("SAMPLE_POLYAREA_WATER").ToLocalChecked(), Nan::New(SAMPLE_POLYAREA_WATER));
    Nan::Set(target, Nan::New("SAMPLE_POLYAREA_ROAD").ToLocalChecked(), Nan::New(SAMPLE_POLYAREA_ROAD));
    Nan::Set(target, Nan::New("SAMPLE_POLYAREA_DOOR").ToLocalChecked(), Nan::New(SAMPLE_POLYAREA_DOOR));
    Nan::Set(target, Nan::New("SAMPLE_POLYAREA_GRASS").ToLocalChecked(), Nan::New(SAMPLE_POLYAREA_GRASS));
    Nan::Set(target, Nan::New("SAMPLE_POLYAREA_JUMP").ToLocalChecked(), Nan::New(SAMPLE_POLYAREA_JUMP));

    Nan::Set(target, Nan::New("SAMPLE_POLYFLAGS_WALK").ToLocalChecked(), Nan::New(SAMPLE_POLYFLAGS_WALK));
    Nan::Set(target, Nan::New("SAMPLE_POLYFLAGS_SWIM").ToLocalChecked(), Nan::New(SAMPLE_POLYFLAGS_SWIM));
    Nan::Set(target, Nan::New("SAMPLE_POLYFLAGS_DOOR").ToLocalChecked(), Nan::New(SAMPLE_POLYFLAGS_DOOR));
    Nan::Set(target, Nan::New("SAMPLE_POLYFLAGS_JUMP").ToLocalChecked(), Nan::New(SAMPLE_POLYFLAGS_JUMP));
    Nan::Set(target, Nan::New("SAMPLE_POLYFLAGS_DISABLED").ToLocalChecked(), Nan::New(SAMPLE_POLYFLAGS_DISABLED));
    Nan::Set(target, Nan::New("SAMPLE_POLYFLAGS_ALL").ToLocalChecked(), Nan::New(SAMPLE_POLYFLAGS_ALL));
    
    Nan::Set(target, Nan::New("DT_STRAIGHTPATH_START").ToLocalChecked(), Nan::New(DT_STRAIGHTPATH_START));
    Nan::Set(target, Nan::New("DT_STRAIGHTPATH_END").ToLocalChecked(), Nan::New(DT_STRAIGHTPATH_END));
    Nan::Set(target, Nan::New("DT_STRAIGHTPATH_OFFMESH_CONNECTION").ToLocalChecked(), Nan::New(DT_STRAIGHTPATH_OFFMESH_CONNECTION));
    
    SampleSoloMeshWrap::Init(target);
    SampleTileMeshWrap::Init(target);
    SampleTempObstaclesWrap::Init(target);
}

NODE_MODULE(addon, Init)
