#include "js-bindings/bindings/axjs_physics_auto.hpp"
#if defined(AX_ENABLE_PHYSICS)
#    include "axmol/axmol.h"
#    include "js-bindings/manual/JSConversions.h"
static void js_register_ax_physics_PhysicsCollider(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::PhysicsCollider> class_PhysicsCollider(isolate);
    class_PhysicsCollider.template inherit<ax::Object>()
        .member_function("getBody", &ax::PhysicsCollider::getBody)
        .member_function("getType", &ax::PhysicsCollider::getType)
        .member_function("getArea", &ax::PhysicsCollider::getArea)
        .member_function("setTag", &ax::PhysicsCollider::setTag)
        .member_function("getTag", &ax::PhysicsCollider::getTag)
        .member_function("getDensity", &ax::PhysicsCollider::getDensity)
        .member_function(
            "setDensity",
            [](ax::PhysicsCollider* self, float arg0) { self->setDensity(arg0); },
            [](ax::PhysicsCollider* self, float arg0, bool arg1) { self->setDensity(arg0, arg1); })
        .member_function("getRestitution", &ax::PhysicsCollider::getRestitution)
        .member_function(
            "setRestitution",
            [](ax::PhysicsCollider* self, float arg0) { self->setRestitution(arg0); },
            [](ax::PhysicsCollider* self, float arg0, bool arg1) { self->setRestitution(arg0, arg1); })
        .member_function("getFriction", &ax::PhysicsCollider::getFriction)
        .member_function(
            "setFriction",
            [](ax::PhysicsCollider* self, float arg0) { self->setFriction(arg0); },
            [](ax::PhysicsCollider* self, float arg0, bool arg1) { self->setFriction(arg0, arg1); })
        .member_function("getMaterial", &ax::PhysicsCollider::getMaterial)
        .member_function("setMaterial", &ax::PhysicsCollider::setMaterial)
        .member_function("isSensor", &ax::PhysicsCollider::isSensor)
        .member_function("setSensor", &ax::PhysicsCollider::setSensor)
        .member_function("getOffset", &ax::PhysicsCollider::getOffset)
        .member_function("getCenter", &ax::PhysicsCollider::getCenter)
        .member_function("containsPoint", &ax::PhysicsCollider::containsPoint)
        .member_function("setCategoryBitmask", &ax::PhysicsCollider::setCategoryBitmask)
        .member_function("getCategoryBitmask", &ax::PhysicsCollider::getCategoryBitmask)
        .member_function("setContactTestBitmask", &ax::PhysicsCollider::setContactTestBitmask)
        .member_function("getContactTestBitmask", &ax::PhysicsCollider::getContactTestBitmask)
        .member_function("setCollisionBitmask", &ax::PhysicsCollider::setCollisionBitmask)
        .member_function("getCollisionBitmask", &ax::PhysicsCollider::getCollisionBitmask)
        .member_function("setGroup", &ax::PhysicsCollider::setGroup)
        .member_function("getGroup", &ax::PhysicsCollider::getGroup)
        .member_function("deatchFromBody", &ax::PhysicsCollider::deatchFromBody)
        .member_function("isDeatched", &ax::PhysicsCollider::isDeatched)
        .static_function(
            "recenterPoints",
            [](ax::Vec2* arg0, int arg1) { ax::PhysicsCollider::recenterPoints(arg0, arg1); },
            [](ax::Vec2* arg0, int arg1, ax::Vec2 arg2) { ax::PhysicsCollider::recenterPoints(arg0, arg1, arg2); })
        .static_function("getPolygonCenter", &ax::PhysicsCollider::getPolygonCenter)
        .auto_wrap_objects(true);
    mod.class_("PhysicsCollider", class_PhysicsCollider);
}
static void js_register_ax_physics_PhysicsColliderCircle(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::PhysicsColliderCircle> class_PhysicsColliderCircle(isolate);
    class_PhysicsColliderCircle.template inherit<ax::PhysicsCollider>()
        .member_function("getRadius", &ax::PhysicsColliderCircle::getRadius)
        .static_function(
            "create",
            [](ax::PhysicsBody* arg0, float arg1) { return ax::PhysicsColliderCircle::create(arg0, arg1); },
            [](ax::PhysicsBody* arg0, float arg1, ax::PhysicsMaterial arg2) { return ax::PhysicsColliderCircle::create(arg0, arg1, arg2); },
            [](ax::PhysicsBody* arg0, float arg1, ax::PhysicsMaterial arg2, ax::Vec2 arg3)
            { return ax::PhysicsColliderCircle::create(arg0, arg1, arg2, arg3); })
        .static_function("calculateArea", &ax::PhysicsColliderCircle::calculateArea)
        .auto_wrap_objects(true);
    mod.class_("PhysicsColliderCircle", class_PhysicsColliderCircle);
}
static void js_register_ax_physics_PhysicsColliderPolygon(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::PhysicsColliderPolygon> class_PhysicsColliderPolygon(isolate);
    class_PhysicsColliderPolygon.template inherit<ax::PhysicsCollider>()
        .member_function("getPoint", &ax::PhysicsColliderPolygon::getPoint)
        .member_function("getPoints", &ax::PhysicsColliderPolygon::getPoints)
        .member_function("getPointsCount", &ax::PhysicsColliderPolygon::getPointsCount)
        .static_function(
            "create",
            [](ax::PhysicsBody* arg0, const ax::Vec2* arg1, int arg2) { return ax::PhysicsColliderPolygon::create(arg0, arg1, arg2); },
            [](ax::PhysicsBody* arg0, const ax::Vec2* arg1, int arg2, ax::PhysicsMaterial arg3)
            { return ax::PhysicsColliderPolygon::create(arg0, arg1, arg2, arg3); },
            [](ax::PhysicsBody* arg0, const ax::Vec2* arg1, int arg2, ax::PhysicsMaterial arg3, ax::Vec2 arg4)
            { return ax::PhysicsColliderPolygon::create(arg0, arg1, arg2, arg3, arg4); },
            [](ax::PhysicsBody* arg0, const ax::Vec2* arg1, int arg2, ax::PhysicsMaterial arg3, ax::Vec2 arg4, float arg5)
            { return ax::PhysicsColliderPolygon::create(arg0, arg1, arg2, arg3, arg4, arg5); })
        .static_function("calculateArea", &ax::PhysicsColliderPolygon::calculateArea)
        .auto_wrap_objects(true);
    mod.class_("PhysicsColliderPolygon", class_PhysicsColliderPolygon);
}
static void js_register_ax_physics_PhysicsColliderBox(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::PhysicsColliderBox> class_PhysicsColliderBox(isolate);
    class_PhysicsColliderBox.template inherit<ax::PhysicsColliderPolygon>()
        .member_function("getSize", &ax::PhysicsColliderBox::getSize)
        .static_function(
            "create",
            [](ax::PhysicsBody* arg0, ax::Vec2 arg1) { return ax::PhysicsColliderBox::create(arg0, arg1); },
            [](ax::PhysicsBody* arg0, ax::Vec2 arg1, ax::PhysicsMaterial arg2) { return ax::PhysicsColliderBox::create(arg0, arg1, arg2); },
            [](ax::PhysicsBody* arg0, ax::Vec2 arg1, ax::PhysicsMaterial arg2, ax::Vec2 arg3)
            { return ax::PhysicsColliderBox::create(arg0, arg1, arg2, arg3); },
            [](ax::PhysicsBody* arg0, ax::Vec2 arg1, ax::PhysicsMaterial arg2, ax::Vec2 arg3, float arg4)
            { return ax::PhysicsColliderBox::create(arg0, arg1, arg2, arg3, arg4); })
        .auto_wrap_objects(true);
    mod.class_("PhysicsColliderBox", class_PhysicsColliderBox);
}
static void js_register_ax_physics_PhysicsColliderEdgeSegment(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::PhysicsColliderEdgeSegment> class_PhysicsColliderEdgeSegment(isolate);
    class_PhysicsColliderEdgeSegment.template inherit<ax::PhysicsCollider>()
        .member_function("getPointA", &ax::PhysicsColliderEdgeSegment::getPointA)
        .member_function("getPointB", &ax::PhysicsColliderEdgeSegment::getPointB)
        .static_function(
            "create",
            [](ax::PhysicsBody* arg0, ax::Vec2 arg1, ax::Vec2 arg2) { return ax::PhysicsColliderEdgeSegment::create(arg0, arg1, arg2); },
            [](ax::PhysicsBody* arg0, ax::Vec2 arg1, ax::Vec2 arg2, ax::PhysicsMaterial arg3)
            { return ax::PhysicsColliderEdgeSegment::create(arg0, arg1, arg2, arg3); },
            [](ax::PhysicsBody* arg0, ax::Vec2 arg1, ax::Vec2 arg2, ax::PhysicsMaterial arg3, float arg4)
            { return ax::PhysicsColliderEdgeSegment::create(arg0, arg1, arg2, arg3, arg4); })
        .auto_wrap_objects(true);
    mod.class_("PhysicsColliderEdgeSegment", class_PhysicsColliderEdgeSegment);
}
static void js_register_ax_physics_PhysicsColliderEdgePolygon(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::PhysicsColliderEdgePolygon> class_PhysicsColliderEdgePolygon(isolate);
    class_PhysicsColliderEdgePolygon.template inherit<ax::PhysicsCollider>()
        .member_function("getPoints", &ax::PhysicsColliderEdgePolygon::getPoints)
        .member_function("getPointsCount", &ax::PhysicsColliderEdgePolygon::getPointsCount)
        .static_function(
            "create",
            [](ax::PhysicsBody* arg0, const ax::Vec2* arg1, int arg2) { return ax::PhysicsColliderEdgePolygon::create(arg0, arg1, arg2); },
            [](ax::PhysicsBody* arg0, const ax::Vec2* arg1, int arg2, ax::PhysicsMaterial arg3)
            { return ax::PhysicsColliderEdgePolygon::create(arg0, arg1, arg2, arg3); },
            [](ax::PhysicsBody* arg0, const ax::Vec2* arg1, int arg2, ax::PhysicsMaterial arg3, float arg4)
            { return ax::PhysicsColliderEdgePolygon::create(arg0, arg1, arg2, arg3, arg4); })
        .auto_wrap_objects(true);
    mod.class_("PhysicsColliderEdgePolygon", class_PhysicsColliderEdgePolygon);
}
static void js_register_ax_physics_PhysicsColliderEdgeBox(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::PhysicsColliderEdgeBox> class_PhysicsColliderEdgeBox(isolate);
    class_PhysicsColliderEdgeBox.template inherit<ax::PhysicsColliderEdgePolygon>()
        .static_function(
            "create",
            [](ax::PhysicsBody* arg0, ax::Vec2 arg1) { return ax::PhysicsColliderEdgeBox::create(arg0, arg1); },
            [](ax::PhysicsBody* arg0, ax::Vec2 arg1, ax::PhysicsMaterial arg2)
            { return ax::PhysicsColliderEdgeBox::create(arg0, arg1, arg2); },
            [](ax::PhysicsBody* arg0, ax::Vec2 arg1, ax::PhysicsMaterial arg2, float arg3)
            { return ax::PhysicsColliderEdgeBox::create(arg0, arg1, arg2, arg3); },
            [](ax::PhysicsBody* arg0, ax::Vec2 arg1, ax::PhysicsMaterial arg2, float arg3, ax::Vec2 arg4)
            { return ax::PhysicsColliderEdgeBox::create(arg0, arg1, arg2, arg3, arg4); })
        .auto_wrap_objects(true);
    mod.class_("PhysicsColliderEdgeBox", class_PhysicsColliderEdgeBox);
}
static void js_register_ax_physics_PhysicsColliderEdgeChain(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::PhysicsColliderEdgeChain> class_PhysicsColliderEdgeChain(isolate);
    class_PhysicsColliderEdgeChain.template inherit<ax::PhysicsCollider>()
        .member_function("getPoints", &ax::PhysicsColliderEdgeChain::getPoints)
        .member_function("getPointsCount", &ax::PhysicsColliderEdgeChain::getPointsCount)
        .static_function(
            "create",
            [](ax::PhysicsBody* arg0, const ax::Vec2* arg1, int arg2) { return ax::PhysicsColliderEdgeChain::create(arg0, arg1, arg2); },
            [](ax::PhysicsBody* arg0, const ax::Vec2* arg1, int arg2, ax::PhysicsMaterial arg3)
            { return ax::PhysicsColliderEdgeChain::create(arg0, arg1, arg2, arg3); },
            [](ax::PhysicsBody* arg0, const ax::Vec2* arg1, int arg2, ax::PhysicsMaterial arg3, float arg4)
            { return ax::PhysicsColliderEdgeChain::create(arg0, arg1, arg2, arg3, arg4); })
        .auto_wrap_objects(true);
    mod.class_("PhysicsColliderEdgeChain", class_PhysicsColliderEdgeChain);
}
static void js_register_ax_physics_PhysicsBody(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::PhysicsBody> class_PhysicsBody(isolate);
    class_PhysicsBody.template inherit<ax::Component>()
        .member_function(
            "addCollider",
            [](ax::PhysicsBody* self, ax::PhysicsCollider* arg0) { return self->addCollider(arg0); },
            [](ax::PhysicsBody* self, ax::PhysicsCollider* arg0, bool arg1) { return self->addCollider(arg0, arg1); })
        .member_function(
            "removeCollider",
            [](ax::PhysicsBody* self, int arg0) { self->removeCollider(arg0); },
            [](ax::PhysicsBody* self, int arg0, bool arg1) { self->removeCollider(arg0, arg1); },
            [](ax::PhysicsBody* self, ax::PhysicsCollider* arg0) { self->removeCollider(arg0); },
            [](ax::PhysicsBody* self, ax::PhysicsCollider* arg0, bool arg1) { self->removeCollider(arg0, arg1); })
        .member_function(
            "removeAllColliders",
            [](ax::PhysicsBody* self) { self->removeAllColliders(); },
            [](ax::PhysicsBody* self, bool arg0) { self->removeAllColliders(arg0); })
        .member_function("getColliders", &ax::PhysicsBody::getColliders)
        .member_function("getFirstCollider", &ax::PhysicsBody::getFirstCollider)
        .member_function("getCollider", &ax::PhysicsBody::getCollider)
        .member_function(
            "applyForce",
            [](ax::PhysicsBody* self, ax::Vec2 arg0) { self->applyForce(arg0); },
            [](ax::PhysicsBody* self, ax::Vec2 arg0, ax::Vec2 arg1) { self->applyForce(arg0, arg1); })
        .member_function("resetForces", &ax::PhysicsBody::resetForces)
        .member_function(
            "applyImpulse",
            [](ax::PhysicsBody* self, ax::Vec2 arg0) { self->applyImpulse(arg0); },
            [](ax::PhysicsBody* self, ax::Vec2 arg0, ax::Vec2 arg1) { self->applyImpulse(arg0, arg1); })
        .member_function("applyTorque", &ax::PhysicsBody::applyTorque)
        .member_function("setVelocity", &ax::PhysicsBody::setVelocity)
        .member_function("getVelocity", &ax::PhysicsBody::getVelocity)
        .member_function("setAngularVelocity", &ax::PhysicsBody::setAngularVelocity)
        .member_function("getVelocityAtLocalPoint", &ax::PhysicsBody::getVelocityAtLocalPoint)
        .member_function("getVelocityAtWorldPoint", &ax::PhysicsBody::getVelocityAtWorldPoint)
        .member_function("getAngularVelocity", &ax::PhysicsBody::getAngularVelocity)
        .member_function("setVelocityLimit", &ax::PhysicsBody::setVelocityLimit)
        .member_function("getVelocityLimit", &ax::PhysicsBody::getVelocityLimit)
        .member_function("setAngularVelocityLimit", &ax::PhysicsBody::setAngularVelocityLimit)
        .member_function("getAngularVelocityLimit", &ax::PhysicsBody::getAngularVelocityLimit)
        .member_function("removeFromWorld", &ax::PhysicsBody::removeFromWorld)
        .member_function("getWorld", &ax::PhysicsBody::getWorld)
        .member_function("getNode", &ax::PhysicsBody::getNode)
        .member_function("setCategoryBitmask", &ax::PhysicsBody::setCategoryBitmask)
        .member_function("setContactTestBitmask", &ax::PhysicsBody::setContactTestBitmask)
        .member_function("setCollisionBitmask", &ax::PhysicsBody::setCollisionBitmask)
        .member_function("getCategoryBitmask", &ax::PhysicsBody::getCategoryBitmask)
        .member_function("getContactTestBitmask", &ax::PhysicsBody::getContactTestBitmask)
        .member_function("getCollisionBitmask", &ax::PhysicsBody::getCollisionBitmask)
        .member_function("setGroup", &ax::PhysicsBody::setGroup)
        .member_function("getGroup", &ax::PhysicsBody::getGroup)
        .member_function("getPosition", &ax::PhysicsBody::getPosition)
        .member_function("getRotation", &ax::PhysicsBody::getRotation)
        .member_function("setPositionOffset", &ax::PhysicsBody::setPositionOffset)
        .member_function("getPositionOffset", &ax::PhysicsBody::getPositionOffset)
        .member_function("setRotationOffset", &ax::PhysicsBody::setRotationOffset)
        .member_function("getRotationOffset", &ax::PhysicsBody::getRotationOffset)
        .member_function("isDynamic", &ax::PhysicsBody::isDynamic)
        .member_function("setDynamic", &ax::PhysicsBody::setDynamic)
        .member_function("getMass", &ax::PhysicsBody::getMass)
        .member_function("getMoment", &ax::PhysicsBody::getMoment)
        .member_function("getLinearDamping", &ax::PhysicsBody::getLinearDamping)
        .member_function("setLinearDamping", &ax::PhysicsBody::setLinearDamping)
        .member_function("getAngularDamping", &ax::PhysicsBody::getAngularDamping)
        .member_function("setAngularDamping", &ax::PhysicsBody::setAngularDamping)
        .member_function("isResting", &ax::PhysicsBody::isResting)
        .member_function("setResting", &ax::PhysicsBody::setResting)
        .member_function("isRotationEnabled", &ax::PhysicsBody::isRotationEnabled)
        .member_function("setRotationEnable", &ax::PhysicsBody::setRotationEnable)
        .member_function("isGravityEnabled", &ax::PhysicsBody::isGravityEnabled)
        .member_function("setGravityEnable", &ax::PhysicsBody::setGravityEnable)
        .member_function("getTag", &ax::PhysicsBody::getTag)
        .member_function("setTag", &ax::PhysicsBody::setTag)
        .member_function("world2Local", &ax::PhysicsBody::world2Local)
        .member_function("local2World", &ax::PhysicsBody::local2World)
        .member_function("getB2Body", &ax::PhysicsBody::getB2Body)
        .member_function("setFixedUpdate", &ax::PhysicsBody::setFixedUpdate)
        .static_function("create", &ax::PhysicsBody::create)
        .static_function(
            "createCircle",
            [](float arg0) { return ax::PhysicsBody::createCircle(arg0); },
            [](float arg0, ax::PhysicsMaterial arg1) { return ax::PhysicsBody::createCircle(arg0, arg1); },
            [](float arg0, ax::PhysicsMaterial arg1, ax::Vec2 arg2) { return ax::PhysicsBody::createCircle(arg0, arg1, arg2); })
        .static_function(
            "createBox",
            [](ax::Vec2 arg0) { return ax::PhysicsBody::createBox(arg0); },
            [](ax::Vec2 arg0, ax::PhysicsMaterial arg1) { return ax::PhysicsBody::createBox(arg0, arg1); },
            [](ax::Vec2 arg0, ax::PhysicsMaterial arg1, ax::Vec2 arg2) { return ax::PhysicsBody::createBox(arg0, arg1, arg2); })
        .static_function(
            "createEdgeSegment",
            [](ax::Vec2 arg0, ax::Vec2 arg1) { return ax::PhysicsBody::createEdgeSegment(arg0, arg1); },
            [](ax::Vec2 arg0, ax::Vec2 arg1, ax::PhysicsMaterial arg2) { return ax::PhysicsBody::createEdgeSegment(arg0, arg1, arg2); },
            [](ax::Vec2 arg0, ax::Vec2 arg1, ax::PhysicsMaterial arg2, float arg3)
            { return ax::PhysicsBody::createEdgeSegment(arg0, arg1, arg2, arg3); })
        .static_function(
            "createEdgeBox",
            [](ax::Vec2 arg0) { return ax::PhysicsBody::createEdgeBox(arg0); },
            [](ax::Vec2 arg0, ax::PhysicsMaterial arg1) { return ax::PhysicsBody::createEdgeBox(arg0, arg1); },
            [](ax::Vec2 arg0, ax::PhysicsMaterial arg1, float arg2) { return ax::PhysicsBody::createEdgeBox(arg0, arg1, arg2); },
            [](ax::Vec2 arg0, ax::PhysicsMaterial arg1, float arg2, ax::Vec2 arg3)
            { return ax::PhysicsBody::createEdgeBox(arg0, arg1, arg2, arg3); })
        .auto_wrap_objects(true);
    mod.class_("PhysicsBody", class_PhysicsBody);
}
static void js_register_ax_physics_PhysicsContact(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::PhysicsContact> class_PhysicsContact(isolate);
    class_PhysicsContact.template inherit<ax::EventCustom>()
        .member_function("getShapeA", &ax::PhysicsContact::getShapeA)
        .member_function("getShapeB", &ax::PhysicsContact::getShapeB)
        .member_function("getContactData", &ax::PhysicsContact::getContactData)
        .member_function("getPreContactData", &ax::PhysicsContact::getPreContactData)
        .member_function("getEventCode", &ax::PhysicsContact::getEventCode)
        .auto_wrap_objects(true);
    mod.class_("PhysicsContact", class_PhysicsContact);
}
static void js_register_ax_physics_PhysicsContactPreSolve(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::PhysicsContactPreSolve> class_PhysicsContactPreSolve(
        isolate, [](v8::Isolate*, const auto&) { /* No constructor class will not be destroyed by script */ });
    class_PhysicsContactPreSolve.member_function("getRestitution", &ax::PhysicsContactPreSolve::getRestitution)
        .member_function("getFriction", &ax::PhysicsContactPreSolve::getFriction)
        .member_function("getSurfaceVelocity", &ax::PhysicsContactPreSolve::getSurfaceVelocity)
        .member_function("setRestitution", &ax::PhysicsContactPreSolve::setRestitution)
        .member_function("setFriction", &ax::PhysicsContactPreSolve::setFriction)
        .member_function("setSurfaceVelocity", &ax::PhysicsContactPreSolve::setSurfaceVelocity)
        .member_function("ignore", &ax::PhysicsContactPreSolve::ignore)
        .auto_wrap_objects(true);
    mod.class_("PhysicsContactPreSolve", class_PhysicsContactPreSolve);
}
static void js_register_ax_physics_PhysicsContactPostSolve(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::PhysicsContactPostSolve> class_PhysicsContactPostSolve(
        isolate, [](v8::Isolate*, const auto&) { /* No constructor class will not be destroyed by script */ });
    class_PhysicsContactPostSolve.member_function("getRestitution", &ax::PhysicsContactPostSolve::getRestitution)
        .member_function("getFriction", &ax::PhysicsContactPostSolve::getFriction)
        .member_function("getSurfaceVelocity", &ax::PhysicsContactPostSolve::getSurfaceVelocity)
        .auto_wrap_objects(true);
    mod.class_("PhysicsContactPostSolve", class_PhysicsContactPostSolve);
}
static void js_register_ax_physics_EventListenerPhysicsContact(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EventListenerPhysicsContact> class_EventListenerPhysicsContact(isolate);
    class_EventListenerPhysicsContact.template inherit<ax::EventListenerCustom>()
        .static_function("create", &ax::EventListenerPhysicsContact::create)
        .auto_wrap_objects(true);
    mod.class_("EventListenerPhysicsContact", class_EventListenerPhysicsContact);
}
static void js_register_ax_physics_EventListenerPhysicsContactWithBodies(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EventListenerPhysicsContactWithBodies> class_EventListenerPhysicsContactWithBodies(isolate);
    class_EventListenerPhysicsContactWithBodies.template inherit<ax::EventListenerPhysicsContact>()
        .member_function("hitTest", &ax::EventListenerPhysicsContactWithBodies::hitTest)
        .static_function("create", &ax::EventListenerPhysicsContactWithBodies::create)
        .auto_wrap_objects(true);
    mod.class_("EventListenerPhysicsContactWithBodies", class_EventListenerPhysicsContactWithBodies);
}
static void js_register_ax_physics_EventListenerPhysicsContactWithShapes(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EventListenerPhysicsContactWithShapes> class_EventListenerPhysicsContactWithShapes(isolate);
    class_EventListenerPhysicsContactWithShapes.template inherit<ax::EventListenerPhysicsContact>()
        .member_function("hitTest", &ax::EventListenerPhysicsContactWithShapes::hitTest)
        .static_function("create", &ax::EventListenerPhysicsContactWithShapes::create)
        .auto_wrap_objects(true);
    mod.class_("EventListenerPhysicsContactWithShapes", class_EventListenerPhysicsContactWithShapes);
}
static void js_register_ax_physics_EventListenerPhysicsContactWithGroup(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EventListenerPhysicsContactWithGroup> class_EventListenerPhysicsContactWithGroup(isolate);
    class_EventListenerPhysicsContactWithGroup.template inherit<ax::EventListenerPhysicsContact>()
        .member_function("hitTest", &ax::EventListenerPhysicsContactWithGroup::hitTest)
        .static_function("create", &ax::EventListenerPhysicsContactWithGroup::create)
        .auto_wrap_objects(true);
    mod.class_("EventListenerPhysicsContactWithGroup", class_EventListenerPhysicsContactWithGroup);
}
static void js_register_ax_physics_PhysicsJoint(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::PhysicsJoint> class_PhysicsJoint(
        isolate, [](v8::Isolate*, const auto&) { /* No constructor class will not be destroyed by script */ });
    class_PhysicsJoint.member_function("getBodyA", &ax::PhysicsJoint::getBodyA)
        .member_function("getBodyB", &ax::PhysicsJoint::getBodyB)
        .member_function("getWorld", &ax::PhysicsJoint::getWorld)
        .member_function("getTag", &ax::PhysicsJoint::getTag)
        .member_function("setTag", &ax::PhysicsJoint::setTag)
        .member_function("isEnabled", &ax::PhysicsJoint::isEnabled)
        .member_function("setEnable", &ax::PhysicsJoint::setEnable)
        .member_function("isCollisionEnabled", &ax::PhysicsJoint::isCollisionEnabled)
        .member_function("setCollisionEnable", &ax::PhysicsJoint::setCollisionEnable)
        .member_function("removeFormWorld", &ax::PhysicsJoint::removeFormWorld)
        .member_function("setMaxForce", &ax::PhysicsJoint::setMaxForce)
        .member_function("getMaxForce", &ax::PhysicsJoint::getMaxForce)
        .auto_wrap_objects(true);
    mod.class_("PhysicsJoint", class_PhysicsJoint);
}
static void js_register_ax_physics_PhysicsJointFixed(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::PhysicsJointFixed> class_PhysicsJointFixed(
        isolate, [](v8::Isolate*, const auto&) { /* No constructor class will not be destroyed by script */ });
    class_PhysicsJointFixed.template inherit<ax::PhysicsJoint>()
        .static_function("instantiate", &ax::PhysicsJointFixed::instantiate)
        .auto_wrap_objects(true);
    mod.class_("PhysicsJointFixed", class_PhysicsJointFixed);
}
static void js_register_ax_physics_PhysicsJointLimit(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::PhysicsJointLimit> class_PhysicsJointLimit(
        isolate, [](v8::Isolate*, const auto&) { /* No constructor class will not be destroyed by script */ });
    class_PhysicsJointLimit.template inherit<ax::PhysicsJoint>()
        .member_function("getAnchr1", &ax::PhysicsJointLimit::getAnchr1)
        .member_function("setAnchr1", &ax::PhysicsJointLimit::setAnchr1)
        .member_function("getAnchr2", &ax::PhysicsJointLimit::getAnchr2)
        .member_function("setAnchr2", &ax::PhysicsJointLimit::setAnchr2)
        .member_function("getMin", &ax::PhysicsJointLimit::getMin)
        .member_function("setMin", &ax::PhysicsJointLimit::setMin)
        .member_function("getMax", &ax::PhysicsJointLimit::getMax)
        .member_function("setMax", &ax::PhysicsJointLimit::setMax)
        .static_function(
            "instantiate",
            [](ax::PhysicsBody* arg0, ax::PhysicsBody* arg1, ax::Vec2 arg2, ax::Vec2 arg3, float arg4, float arg5)
            { return ax::PhysicsJointLimit::instantiate(arg0, arg1, arg2, arg3, arg4, arg5); },
            [](ax::PhysicsBody* arg0, ax::PhysicsBody* arg1, ax::Vec2 arg2, ax::Vec2 arg3)
            { return ax::PhysicsJointLimit::instantiate(arg0, arg1, arg2, arg3); })
        .auto_wrap_objects(true);
    mod.class_("PhysicsJointLimit", class_PhysicsJointLimit);
}
static void js_register_ax_physics_PhysicsJointPin(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::PhysicsJointPin> class_PhysicsJointPin(
        isolate, [](v8::Isolate*, const auto&) { /* No constructor class will not be destroyed by script */ });
    class_PhysicsJointPin.template inherit<ax::PhysicsJoint>()
        .static_function(
            "instantiate",
            [](ax::PhysicsBody* arg0, ax::PhysicsBody* arg1, ax::Vec2 arg2, ax::Vec2 arg3)
            { return ax::PhysicsJointPin::instantiate(arg0, arg1, arg2, arg3); },
            [](ax::PhysicsBody* arg0, ax::PhysicsBody* arg1, ax::Vec2 arg2) { return ax::PhysicsJointPin::instantiate(arg0, arg1, arg2); })
        .auto_wrap_objects(true);
    mod.class_("PhysicsJointPin", class_PhysicsJointPin);
}
static void js_register_ax_physics_PhysicsJointDistance(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::PhysicsJointDistance> class_PhysicsJointDistance(
        isolate, [](v8::Isolate*, const auto&) { /* No constructor class will not be destroyed by script */ });
    class_PhysicsJointDistance.template inherit<ax::PhysicsJoint>()
        .member_function("getDistance", &ax::PhysicsJointDistance::getDistance)
        .member_function("setDistance", &ax::PhysicsJointDistance::setDistance)
        .static_function("instantiate", &ax::PhysicsJointDistance::instantiate)
        .auto_wrap_objects(true);
    mod.class_("PhysicsJointDistance", class_PhysicsJointDistance);
}
static void js_register_ax_physics_PhysicsJointSpring(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::PhysicsJointSpring> class_PhysicsJointSpring(
        isolate, [](v8::Isolate*, const auto&) { /* No constructor class will not be destroyed by script */ });
    class_PhysicsJointSpring.template inherit<ax::PhysicsJoint>()
        .member_function("getAnchr1", &ax::PhysicsJointSpring::getAnchr1)
        .member_function("setAnchr1", &ax::PhysicsJointSpring::setAnchr1)
        .member_function("getAnchr2", &ax::PhysicsJointSpring::getAnchr2)
        .member_function("setAnchr2", &ax::PhysicsJointSpring::setAnchr2)
        .member_function("getRestLength", &ax::PhysicsJointSpring::getRestLength)
        .member_function("setRestLength", &ax::PhysicsJointSpring::setRestLength)
        .member_function("getStiffness", &ax::PhysicsJointSpring::getStiffness)
        .member_function("setStiffness", &ax::PhysicsJointSpring::setStiffness)
        .member_function("getDamping", &ax::PhysicsJointSpring::getDamping)
        .member_function("setDamping", &ax::PhysicsJointSpring::setDamping)
        .static_function("instantiate", &ax::PhysicsJointSpring::instantiate)
        .auto_wrap_objects(true);
    mod.class_("PhysicsJointSpring", class_PhysicsJointSpring);
}
static void js_register_ax_physics_PhysicsJointGroove(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::PhysicsJointGroove> class_PhysicsJointGroove(
        isolate, [](v8::Isolate*, const auto&) { /* No constructor class will not be destroyed by script */ });
    class_PhysicsJointGroove.template inherit<ax::PhysicsJoint>()
        .member_function("getGrooveA", &ax::PhysicsJointGroove::getGrooveA)
        .member_function("setGrooveA", &ax::PhysicsJointGroove::setGrooveA)
        .member_function("getGrooveB", &ax::PhysicsJointGroove::getGrooveB)
        .member_function("setGrooveB", &ax::PhysicsJointGroove::setGrooveB)
        .member_function("getAnchr2", &ax::PhysicsJointGroove::getAnchr2)
        .member_function("setAnchr2", &ax::PhysicsJointGroove::setAnchr2)
        .static_function("instantiate", &ax::PhysicsJointGroove::instantiate)
        .auto_wrap_objects(true);
    mod.class_("PhysicsJointGroove", class_PhysicsJointGroove);
}
static void js_register_ax_physics_PhysicsJointRotarySpring(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::PhysicsJointRotarySpring> class_PhysicsJointRotarySpring(
        isolate, [](v8::Isolate*, const auto&) { /* No constructor class will not be destroyed by script */ });
    class_PhysicsJointRotarySpring.template inherit<ax::PhysicsJoint>()
        .member_function("getRestAngle", &ax::PhysicsJointRotarySpring::getRestAngle)
        .member_function("setRestAngle", &ax::PhysicsJointRotarySpring::setRestAngle)
        .member_function("getStiffness", &ax::PhysicsJointRotarySpring::getStiffness)
        .member_function("setStiffness", &ax::PhysicsJointRotarySpring::setStiffness)
        .member_function("getDamping", &ax::PhysicsJointRotarySpring::getDamping)
        .member_function("setDamping", &ax::PhysicsJointRotarySpring::setDamping)
        .static_function("instantiate", &ax::PhysicsJointRotarySpring::instantiate)
        .auto_wrap_objects(true);
    mod.class_("PhysicsJointRotarySpring", class_PhysicsJointRotarySpring);
}
static void js_register_ax_physics_PhysicsJointRotaryLimit(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::PhysicsJointRotaryLimit> class_PhysicsJointRotaryLimit(
        isolate, [](v8::Isolate*, const auto&) { /* No constructor class will not be destroyed by script */ });
    class_PhysicsJointRotaryLimit.template inherit<ax::PhysicsJoint>()
        .member_function("getMin", &ax::PhysicsJointRotaryLimit::getMin)
        .member_function("setMin", &ax::PhysicsJointRotaryLimit::setMin)
        .member_function("getMax", &ax::PhysicsJointRotaryLimit::getMax)
        .member_function("setMax", &ax::PhysicsJointRotaryLimit::setMax)
        .static_function(
            "instantiate",
            [](ax::PhysicsBody* arg0, ax::PhysicsBody* arg1) { return ax::PhysicsJointRotaryLimit::instantiate(arg0, arg1); },
            [](ax::PhysicsBody* arg0, ax::PhysicsBody* arg1, float arg2, float arg3)
            { return ax::PhysicsJointRotaryLimit::instantiate(arg0, arg1, arg2, arg3); })
        .auto_wrap_objects(true);
    mod.class_("PhysicsJointRotaryLimit", class_PhysicsJointRotaryLimit);
}
static void js_register_ax_physics_PhysicsJointRatchet(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::PhysicsJointRatchet> class_PhysicsJointRatchet(
        isolate, [](v8::Isolate*, const auto&) { /* No constructor class will not be destroyed by script */ });
    class_PhysicsJointRatchet.template inherit<ax::PhysicsJoint>()
        .member_function("getAngle", &ax::PhysicsJointRatchet::getAngle)
        .member_function("setAngle", &ax::PhysicsJointRatchet::setAngle)
        .member_function("getPhase", &ax::PhysicsJointRatchet::getPhase)
        .member_function("setPhase", &ax::PhysicsJointRatchet::setPhase)
        .member_function("getRatchet", &ax::PhysicsJointRatchet::getRatchet)
        .member_function("setRatchet", &ax::PhysicsJointRatchet::setRatchet)
        .static_function("instantiate", &ax::PhysicsJointRatchet::instantiate)
        .auto_wrap_objects(true);
    mod.class_("PhysicsJointRatchet", class_PhysicsJointRatchet);
}
static void js_register_ax_physics_PhysicsJointGear(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::PhysicsJointGear> class_PhysicsJointGear(
        isolate, [](v8::Isolate*, const auto&) { /* No constructor class will not be destroyed by script */ });
    class_PhysicsJointGear.template inherit<ax::PhysicsJoint>()
        .member_function("getPhase", &ax::PhysicsJointGear::getPhase)
        .member_function("setPhase", &ax::PhysicsJointGear::setPhase)
        .member_function("getRatio", &ax::PhysicsJointGear::getRatio)
        .member_function("setRatio", &ax::PhysicsJointGear::setRatio)
        .static_function("instantiate", &ax::PhysicsJointGear::instantiate)
        .auto_wrap_objects(true);
    mod.class_("PhysicsJointGear", class_PhysicsJointGear);
}
static void js_register_ax_physics_PhysicsJointMotor(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::PhysicsJointMotor> class_PhysicsJointMotor(
        isolate, [](v8::Isolate*, const auto&) { /* No constructor class will not be destroyed by script */ });
    class_PhysicsJointMotor.template inherit<ax::PhysicsJoint>()
        .member_function("getRate", &ax::PhysicsJointMotor::getRate)
        .member_function("setRate", &ax::PhysicsJointMotor::setRate)
        .static_function("instantiate", &ax::PhysicsJointMotor::instantiate)
        .auto_wrap_objects(true);
    mod.class_("PhysicsJointMotor", class_PhysicsJointMotor);
}
static void js_register_ax_physics_PhysicsWorld(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::PhysicsWorld> class_PhysicsWorld(
        isolate, [](v8::Isolate*, const auto&) { /* No constructor class will not be destroyed by script */ });
    class_PhysicsWorld.member_function("getB2World", &ax::PhysicsWorld::getB2World)
        .member_function("addJoint", &ax::PhysicsWorld::addJoint)
        .member_function(
            "removeJoint",
            [](ax::PhysicsWorld* self, ax::PhysicsJoint* arg0) { self->removeJoint(arg0); },
            [](ax::PhysicsWorld* self, ax::PhysicsJoint* arg0, bool arg1) { self->removeJoint(arg0, arg1); })
        .member_function(
            "removeAllJoints",
            [](ax::PhysicsWorld* self) { self->removeAllJoints(); },
            [](ax::PhysicsWorld* self, bool arg0) { self->removeAllJoints(arg0); })
        .member_function(
            "removeBody",
            [](ax::PhysicsWorld* self, int arg0) { self->removeBody(arg0); },
            [](ax::PhysicsWorld* self, ax::PhysicsBody* arg0) { self->removeBody(arg0); })
        .member_function("removeAllBodies", &ax::PhysicsWorld::removeAllBodies)
        .member_function("getShapes", &ax::PhysicsWorld::getShapes)
        .member_function("getShape", &ax::PhysicsWorld::getShape)
        .member_function("getAllBodies", &ax::PhysicsWorld::getAllBodies)
        .member_function("getBody", &ax::PhysicsWorld::getBody)
        .member_function("getGravity", &ax::PhysicsWorld::getGravity)
        .member_function("setGravity", &ax::PhysicsWorld::setGravity)
        .member_function("setSlopBias", &ax::PhysicsWorld::setSlopBias)
        .member_function("setSpeed", &ax::PhysicsWorld::setSpeed)
        .member_function("getSpeed", &ax::PhysicsWorld::getSpeed)
        .member_function("setUpdateRate", &ax::PhysicsWorld::setUpdateRate)
        .member_function("getUpdateRate", &ax::PhysicsWorld::getUpdateRate)
        .member_function("setSubsteps", &ax::PhysicsWorld::setSubsteps)
        .member_function("getSubsteps", &ax::PhysicsWorld::getSubsteps)
        .member_function("setFixedUpdateRate", &ax::PhysicsWorld::setFixedUpdateRate)
        .member_function("getFixedUpdateRate", &ax::PhysicsWorld::getFixedUpdateRate)
        .member_function("setPreUpdateCallback", &ax::PhysicsWorld::setPreUpdateCallback)
        .member_function("setPostUpdateCallback", &ax::PhysicsWorld::setPostUpdateCallback)
        .member_function("setAutoStep", &ax::PhysicsWorld::setAutoStep)
        .member_function("isAutoStep", &ax::PhysicsWorld::isAutoStep)
        .member_function("step", &ax::PhysicsWorld::step)
        .auto_wrap_objects(true);
    mod.class_("PhysicsWorld", class_PhysicsWorld);
}
void js_register_all_ax_physics(JsRegistry& registry)
{
    v8pp::module& mod = registry.module("ax");
    js_register_ax_physics_PhysicsCollider(mod);
    js_register_ax_physics_PhysicsColliderCircle(mod);
    js_register_ax_physics_PhysicsColliderPolygon(mod);
    js_register_ax_physics_PhysicsColliderBox(mod);
    js_register_ax_physics_PhysicsColliderEdgeSegment(mod);
    js_register_ax_physics_PhysicsColliderEdgePolygon(mod);
    js_register_ax_physics_PhysicsColliderEdgeBox(mod);
    js_register_ax_physics_PhysicsColliderEdgeChain(mod);
    js_register_ax_physics_PhysicsBody(mod);
    js_register_ax_physics_PhysicsContact(mod);
    js_register_ax_physics_PhysicsContactPreSolve(mod);
    js_register_ax_physics_PhysicsContactPostSolve(mod);
    js_register_ax_physics_EventListenerPhysicsContact(mod);
    js_register_ax_physics_EventListenerPhysicsContactWithBodies(mod);
    js_register_ax_physics_EventListenerPhysicsContactWithShapes(mod);
    js_register_ax_physics_EventListenerPhysicsContactWithGroup(mod);
    js_register_ax_physics_PhysicsJoint(mod);
    js_register_ax_physics_PhysicsJointFixed(mod);
    js_register_ax_physics_PhysicsJointLimit(mod);
    js_register_ax_physics_PhysicsJointPin(mod);
    js_register_ax_physics_PhysicsJointDistance(mod);
    js_register_ax_physics_PhysicsJointSpring(mod);
    js_register_ax_physics_PhysicsJointGroove(mod);
    js_register_ax_physics_PhysicsJointRotarySpring(mod);
    js_register_ax_physics_PhysicsJointRotaryLimit(mod);
    js_register_ax_physics_PhysicsJointRatchet(mod);
    js_register_ax_physics_PhysicsJointGear(mod);
    js_register_ax_physics_PhysicsJointMotor(mod);
    js_register_ax_physics_PhysicsWorld(mod);
}
#endif
