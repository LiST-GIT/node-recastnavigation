#include "SampleTempObstaclesWrap.hpp"

Nan::Persistent<v8::FunctionTemplate> SampleTempObstaclesWrap::constructor;

NAN_MODULE_INIT(SampleTempObstaclesWrap::Init) {
    Nan::HandleScope scope;
    Local<FunctionTemplate> t = Nan::New<FunctionTemplate>(New);
    t->InstanceTemplate()->SetInternalFieldCount(1);
    t->SetClassName(Nan::New("SampleTempObstacles").ToLocalChecked());
    Nan::SetPrototypeMethod(t, "load", Load);
    Nan::SetPrototypeMethod(t, "addOffMeshConnection", AddOffMeshConnection);
    Nan::SetPrototypeMethod(t, "deleteOffMeshConnection", DeleteOffMeshConnection);
    Nan::SetPrototypeMethod(t, "getOffMeshConnectionCount", GetOffMeshConnectionCount);
    Nan::SetPrototypeMethod(t, "build", Build);
    Nan::SetPrototypeMethod(t, "findPath", FindPath);
    Nan::SetPrototypeMethod(t, "findNearestPoly", FindNearestPoly);
    constructor.Reset(t);
    Nan::Set(target, Nan::New("SampleTempObstacles").ToLocalChecked(), Nan::GetFunction(t).ToLocalChecked());
}

NAN_METHOD(SampleTempObstaclesWrap::New) {
    if (!info.IsConstructCall()) {
        return Nan::ThrowTypeError("Use the new operator to create new objects");
    }
    SampleTempObstaclesWrap *obj = new SampleTempObstaclesWrap();
    obj->setContext(new BuildContext());
    obj->handleMeshChanged(new InputGeom());
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
}

NAN_METHOD(SampleTempObstaclesWrap::Load) {
    SampleTempObstaclesWrap *thisobj = Nan::ObjectWrap::Unwrap<SampleTempObstaclesWrap>(info.This());
    Nan::Utf8String filename(info[0]);
    thisobj->loadAll(*filename);
    info.GetReturnValue().Set(Nan::Null());
}

NAN_METHOD(SampleTempObstaclesWrap::AddOffMeshConnection) {
    SampleTempObstaclesWrap *thisobj = Nan::ObjectWrap::Unwrap<SampleTempObstaclesWrap>(info.This());
    const float startPos[3] = {
        (float)Nan::To<double>(info[0]).FromJust(),
        (float)Nan::To<double>(info[1]).FromJust(),
        (float)Nan::To<double>(info[2]).FromJust(),
    };
    const float endPos[3] = {
        (float)Nan::To<double>(info[3]).FromJust(),
        (float)Nan::To<double>(info[4]).FromJust(),
        (float)Nan::To<double>(info[5]).FromJust(),
    };
    float rad = Nan::To<double>(info[6]).FromJust();
    int bidir = Nan::To<int>(info[7]).FromJust();
    int area = Nan::To<int>(info[8]).FromJust();
    int flags = Nan::To<int>(info[9]).FromJust();
    thisobj->getInputGeom()->addOffMeshConnection(startPos, endPos, rad, bidir, area, flags);
    info.GetReturnValue().Set(thisobj->getInputGeom()->getOffMeshConnectionCount());
}

NAN_METHOD(SampleTempObstaclesWrap::DeleteOffMeshConnection) {
    SampleTempObstaclesWrap *thisobj = Nan::ObjectWrap::Unwrap<SampleTempObstaclesWrap>(info.This());
    int index = Nan::To<int32_t>(info[0]).FromJust();
    thisobj->getInputGeom()->deleteOffMeshConnection(index);
    info.GetReturnValue().Set(thisobj->getInputGeom()->getOffMeshConnectionCount());
}

NAN_METHOD(SampleTempObstaclesWrap::GetOffMeshConnectionCount) {
    SampleTempObstaclesWrap *thisobj = Nan::ObjectWrap::Unwrap<SampleTempObstaclesWrap>(info.This());
    info.GetReturnValue().Set(thisobj->getInputGeom()->getOffMeshConnectionCount());
}

NAN_METHOD(SampleTempObstaclesWrap::Build) {
    SampleTempObstaclesWrap *thisobj = Nan::ObjectWrap::Unwrap<SampleTempObstaclesWrap>(info.This());
    info.GetReturnValue().Set(thisobj->handleBuild());
}

NAN_METHOD(SampleTempObstaclesWrap::FindPath) {
    SampleTempObstaclesWrap *thisobj = Nan::ObjectWrap::Unwrap<SampleTempObstaclesWrap>(info.This());
    const float startCenterPos[3] = {
        (float)Nan::To<double>(info[0]).FromJust(),
        (float)Nan::To<double>(info[1]).FromJust(),
        (float)Nan::To<double>(info[2]).FromJust(),
    };
    const float endCenterPos[3] = {
        (float)Nan::To<double>(info[3]).FromJust(),
        (float)Nan::To<double>(info[4]).FromJust(),
        (float)Nan::To<double>(info[5]).FromJust(),
    };
    const float extents[3] = {
        2,
        4,
        2,
    };
    dtQueryFilter filter;
    filter.setAreaCost(SAMPLE_POLYAREA_GROUND, 1.0f);
    filter.setAreaCost(SAMPLE_POLYAREA_WATER, 10.0f);
    filter.setAreaCost(SAMPLE_POLYAREA_ROAD, 1.0f);
    filter.setAreaCost(SAMPLE_POLYAREA_DOOR, 1.0f);
    filter.setAreaCost(SAMPLE_POLYAREA_GRASS, 2.0f);
    filter.setAreaCost(SAMPLE_POLYAREA_JUMP, 1.5f);
    filter.setIncludeFlags(SAMPLE_POLYFLAGS_ALL);
    filter.setExcludeFlags(0);
    dtPolyRef startRef = 0;
    float startPos[3];
    dtPolyRef endRef = 0;
    float endPos[3];
    int maxPath = Nan::To<double>(info[6]).FromJust();
    int pathCount;
    dtPolyRef path[maxPath];
    dtNavMeshQuery *navMeshQuery = thisobj->getNavMeshQuery();
    if (dtStatusFailed(navMeshQuery->findNearestPoly(startCenterPos, extents, &filter, &startRef, startPos))) {
        info.GetReturnValue().Set(Nan::Null()); 
        return;
    }
    if (dtStatusFailed(navMeshQuery->findNearestPoly(endCenterPos, extents, &filter, &endRef, endPos))) {
        info.GetReturnValue().Set(Nan::Null()); 
        return;
    }
    if (dtStatusFailed(navMeshQuery->findPath(startRef, endRef, startPos, endPos, &filter, path, &pathCount, maxPath))) {
        info.GetReturnValue().Set(Nan::Null()); 
        return;
    }
    float straightPath[maxPath * 3];
    unsigned char straightPathFlags[maxPath];
    dtPolyRef straightPathRefs[maxPath];
    int straightPathCount = 0;
    if (dtStatusFailed(navMeshQuery->findStraightPath(startPos, endPos, path, pathCount, straightPath, straightPathFlags, straightPathRefs, &straightPathCount, maxPath, 0))) {
        info.GetReturnValue().Set(Nan::Null()); 
        return;
    }
    v8::Local<v8::Array> result = Nan::New<v8::Array>(straightPathCount);
    for (int index = 0; index < straightPathCount; index++) {
        v8::Local<v8::Object> vector3 = Nan::New<v8::Object>();
        const int cursor = index * 3;
        Nan::Set(vector3, Nan::New("x").ToLocalChecked(), Nan::New(straightPath[cursor + 0]));
        Nan::Set(vector3, Nan::New("y").ToLocalChecked(), Nan::New(straightPath[cursor + 1]));
        Nan::Set(vector3, Nan::New("z").ToLocalChecked(), Nan::New(straightPath[cursor + 2]));
        Nan::Set(vector3, Nan::New("ref").ToLocalChecked(), Nan::New(straightPathRefs[index]));
        Nan::Set(vector3, Nan::New("flags").ToLocalChecked(), Nan::New(straightPathFlags[index]));
        Nan::Set(result, index, vector3);
    }
    info.GetReturnValue().Set(result);
}

NAN_METHOD(SampleTempObstaclesWrap::FindNearestPoly) {
    SampleTempObstaclesWrap *thisobj = Nan::ObjectWrap::Unwrap<SampleTempObstaclesWrap>(info.This());
     const float center[3] = {
        (float)Nan::To<double>(info[0]).FromJust(),
        (float)Nan::To<double>(info[1]).FromJust(),
        (float)Nan::To<double>(info[2]).FromJust(),
    };
    const float extents[3] = {
        (float)Nan::To<double>(info[3]).FromJust(),
        (float)Nan::To<double>(info[4]).FromJust(),
        (float)Nan::To<double>(info[5]).FromJust(),
    };
    dtQueryFilter filter;
    filter.setIncludeFlags(SAMPLE_POLYFLAGS_WALK | SAMPLE_POLYFLAGS_SWIM);
    filter.setExcludeFlags(0);
    dtPolyRef nearestRef = 0;
    float nearestPt[3];
    if (dtStatusFailed(thisobj->getNavMeshQuery()->findNearestPoly(center, extents, &filter, &nearestRef, nearestPt))) {
        info.GetReturnValue().Set(Nan::Null()); 
        return;
    }
    v8::Local<v8::Object> result = Nan::New<v8::Object>();
    Nan::Set(result, Nan::New("x").ToLocalChecked(), Nan::New(nearestPt[0]));
    Nan::Set(result, Nan::New("y").ToLocalChecked(), Nan::New(nearestPt[1]));
    Nan::Set(result, Nan::New("z").ToLocalChecked(), Nan::New(nearestPt[2]));
    Nan::Set(result, Nan::New("ref").ToLocalChecked(), Nan::New(nearestRef));
    info.GetReturnValue().Set(result);
}
