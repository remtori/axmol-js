#include "js-bindings/bindings/axjs_navmesh_auto.hpp"
#if defined(AX_ENABLE_NAVMESH)
#    include "axmol/navmesh/NavMesh.h"
#    include "js-bindings/manual/JSConversions.h"
static void js_register_ax_navmesh_NavMeshAgent(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::NavMeshAgent> class_NavMeshAgent(isolate);
    class_NavMeshAgent.ctor([]() { return new ax::NavMeshAgent(); })
        .template inherit<ax::Component>()
        .member_function("setRadius", &ax::NavMeshAgent::setRadius)
        .member_function("getRadius", &ax::NavMeshAgent::getRadius)
        .member_function("setHeight", &ax::NavMeshAgent::setHeight)
        .member_function("getHeight", &ax::NavMeshAgent::getHeight)
        .member_function("setMaxAcceleration", &ax::NavMeshAgent::setMaxAcceleration)
        .member_function("getMaxAcceleration", &ax::NavMeshAgent::getMaxAcceleration)
        .member_function("setMaxSpeed", &ax::NavMeshAgent::setMaxSpeed)
        .member_function("getMaxSpeed", &ax::NavMeshAgent::getMaxSpeed)
        .member_function("setSeparationWeight", &ax::NavMeshAgent::setSeparationWeight)
        .member_function("getSeparationWeight", &ax::NavMeshAgent::getSeparationWeight)
        .member_function("setObstacleAvoidanceType", &ax::NavMeshAgent::setObstacleAvoidanceType)
        .member_function("getObstacleAvoidanceType", &ax::NavMeshAgent::getObstacleAvoidanceType)
        .member_function("getCurrentVelocity", &ax::NavMeshAgent::getCurrentVelocity)
        .member_function("pause", &ax::NavMeshAgent::pause)
        .member_function("resume", &ax::NavMeshAgent::resume)
        .member_function("stop", &ax::NavMeshAgent::stop)
        .member_function("setOrientationRefAxes", &ax::NavMeshAgent::setOrientationRefAxes)
        .member_function("setAutoOrientation", &ax::NavMeshAgent::setAutoOrientation)
        .member_function("setAutoTraverseOffMeshLink", &ax::NavMeshAgent::setAutoTraverseOffMeshLink)
        .member_function("isOnOffMeshLink", &ax::NavMeshAgent::isOnOffMeshLink)
        .member_function("completeOffMeshLink", &ax::NavMeshAgent::completeOffMeshLink)
        .member_function("getCurrentOffMeshLinkData", &ax::NavMeshAgent::getCurrentOffMeshLinkData)
        .member_function("setUserData", &ax::NavMeshAgent::setUserData)
        .member_function("getUserData", &ax::NavMeshAgent::getUserData)
        .member_function("setSyncFlag", &ax::NavMeshAgent::setSyncFlag)
        .member_function("getSyncFlag", &ax::NavMeshAgent::getSyncFlag)
        .member_function("syncToAgent", &ax::NavMeshAgent::syncToAgent)
        .member_function("syncToNode", &ax::NavMeshAgent::syncToNode)
        .member_function("getVelocity", &ax::NavMeshAgent::getVelocity)
        .static_function("create", &ax::NavMeshAgent::create)
        .static_function("getNavMeshAgentComponentName", &ax::NavMeshAgent::getNavMeshAgentComponentName)
        .auto_wrap_objects(true);
    mod.class_("NavMeshAgent", class_NavMeshAgent);
}
static void js_register_ax_navmesh_NavMeshObstacle(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::NavMeshObstacle> class_NavMeshObstacle(isolate);
    class_NavMeshObstacle.ctor([]() { return new ax::NavMeshObstacle(); })
        .template inherit<ax::Component>()
        .member_function("getRadius", &ax::NavMeshObstacle::getRadius)
        .member_function("getHeight", &ax::NavMeshObstacle::getHeight)
        .member_function("setSyncFlag", &ax::NavMeshObstacle::setSyncFlag)
        .member_function("getSyncFlag", &ax::NavMeshObstacle::getSyncFlag)
        .member_function("syncToObstacle", &ax::NavMeshObstacle::syncToObstacle)
        .member_function("syncToNode", &ax::NavMeshObstacle::syncToNode)
        .member_function("initWith", &ax::NavMeshObstacle::initWith)
        .static_function("create", &ax::NavMeshObstacle::create)
        .static_function("getNavMeshObstacleComponentName", &ax::NavMeshObstacle::getNavMeshObstacleComponentName)
        .auto_wrap_objects(true);
    mod.class_("NavMeshObstacle", class_NavMeshObstacle);
}
static void js_register_ax_navmesh_NavMesh(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::NavMesh> class_NavMesh(isolate);
    class_NavMesh.ctor([]() { return new ax::NavMesh(); })
        .template inherit<ax::Object>()
        .member_function("update", &ax::NavMesh::update)
        .member_function("debugDraw", &ax::NavMesh::debugDraw)
        .member_function("setDebugDrawEnable", &ax::NavMesh::setDebugDrawEnable)
        .member_function("isDebugDrawEnabled", &ax::NavMesh::isDebugDrawEnabled)
        .member_function("addNavMeshAgent", &ax::NavMesh::addNavMeshAgent)
        .member_function("removeNavMeshAgent", &ax::NavMesh::removeNavMeshAgent)
        .member_function("addNavMeshObstacle", &ax::NavMesh::addNavMeshObstacle)
        .member_function("removeNavMeshObstacle", &ax::NavMesh::removeNavMeshObstacle)
        .static_function("create", &ax::NavMesh::create)
        .auto_wrap_objects(true);
    mod.class_("NavMesh", class_NavMesh);
}
void js_register_all_ax_navmesh(JsRegistry& registry)
{
    v8pp::module& mod = registry.module("ax");
    js_register_ax_navmesh_NavMeshAgent(mod);
    js_register_ax_navmesh_NavMeshObstacle(mod);
    js_register_ax_navmesh_NavMesh(mod);
}
#endif
