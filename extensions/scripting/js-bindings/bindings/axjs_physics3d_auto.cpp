#include "js-bindings/bindings/axjs_physics3d_auto.hpp"
#if defined(AX_ENABLE_3D_PHYSICS)
#    include "axmol/physics3d/Physics3D.h"
#    include "js-bindings/manual/JSConversions.h"
static void js_register_ax_physics3d_Physics3DShape(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Physics3DShape> class_Physics3DShape(isolate);
    class_Physics3DShape.ctor([]() { return new ax::Physics3DShape(); })
        .template inherit<ax::Object>()
        .member_function("getShapeType", &ax::Physics3DShape::getShapeType)
        .member_function("getbtShape", &ax::Physics3DShape::getbtShape)
        .member_function("initBox", &ax::Physics3DShape::initBox)
        .member_function("initSphere", &ax::Physics3DShape::initSphere)
        .member_function("initCylinder", &ax::Physics3DShape::initCylinder)
        .member_function("initCapsule", &ax::Physics3DShape::initCapsule)
        .static_function("createBox", &ax::Physics3DShape::createBox)
        .static_function("createSphere", &ax::Physics3DShape::createSphere)
        .static_function("createCylinder", &ax::Physics3DShape::createCylinder)
        .static_function("createCapsule", &ax::Physics3DShape::createCapsule)
        .static_function("createConvexHull", &ax::Physics3DShape::createConvexHull)
        .auto_wrap_objects(true);
    mod.class_("Physics3DShape", class_Physics3DShape);
}
static void js_register_ax_physics3d_Physics3DObject(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Physics3DObject> class_Physics3DObject(isolate);
    class_Physics3DObject.template inherit<ax::Object>()
        .member_function("getObjType", &ax::Physics3DObject::getObjType)
        .member_function("setPhysicsWorld", &ax::Physics3DObject::setPhysicsWorld)
        .member_function("getPhysicsWorld", &ax::Physics3DObject::getPhysicsWorld)
        .member_function("getWorldTransform", &ax::Physics3DObject::getWorldTransform)
        .member_function("getCollisionCallback", &ax::Physics3DObject::getCollisionCallback)
        .member_function("needCollisionCallback", &ax::Physics3DObject::needCollisionCallback)
        .member_function("setMask", &ax::Physics3DObject::setMask)
        .member_function("getMask", &ax::Physics3DObject::getMask)
        .auto_wrap_objects(true);
    mod.class_("Physics3DObject", class_Physics3DObject);
}
static void js_register_ax_physics3d_Physics3DRigidBody(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Physics3DRigidBody> class_Physics3DRigidBody(isolate);
    class_Physics3DRigidBody.ctor([]() { return new ax::Physics3DRigidBody(); })
        .template inherit<ax::Physics3DObject>()
        .member_function("getRigidBody", &ax::Physics3DRigidBody::getRigidBody)
        .member_function("applyForce", &ax::Physics3DRigidBody::applyForce)
        .member_function("applyCentralForce", &ax::Physics3DRigidBody::applyCentralForce)
        .member_function("applyCentralImpulse", &ax::Physics3DRigidBody::applyCentralImpulse)
        .member_function("applyTorque", &ax::Physics3DRigidBody::applyTorque)
        .member_function("applyTorqueImpulse", &ax::Physics3DRigidBody::applyTorqueImpulse)
        .member_function("applyImpulse", &ax::Physics3DRigidBody::applyImpulse)
        .member_function("applyDamping", &ax::Physics3DRigidBody::applyDamping)
        .member_function("setLinearVelocity", &ax::Physics3DRigidBody::setLinearVelocity)
        .member_function("getLinearVelocity", &ax::Physics3DRigidBody::getLinearVelocity)
        .member_function("setLinearFactor", &ax::Physics3DRigidBody::setLinearFactor)
        .member_function("getLinearFactor", &ax::Physics3DRigidBody::getLinearFactor)
        .member_function(
            "setAngularFactor",
            [](ax::Physics3DRigidBody* self, float arg0) { self->setAngularFactor(arg0); },
            [](ax::Physics3DRigidBody* self, ax::Vec3 arg0) { self->setAngularFactor(arg0); })
        .member_function("getAngularFactor", &ax::Physics3DRigidBody::getAngularFactor)
        .member_function("setAngularVelocity", &ax::Physics3DRigidBody::setAngularVelocity)
        .member_function("getAngularVelocity", &ax::Physics3DRigidBody::getAngularVelocity)
        .member_function("setCenterOfMassTransform", &ax::Physics3DRigidBody::setCenterOfMassTransform)
        .member_function("getCenterOfMassTransform", &ax::Physics3DRigidBody::getCenterOfMassTransform)
        .member_function("setDamping", &ax::Physics3DRigidBody::setDamping)
        .member_function("getLinearDamping", &ax::Physics3DRigidBody::getLinearDamping)
        .member_function("getAngularDamping", &ax::Physics3DRigidBody::getAngularDamping)
        .member_function("setGravity", &ax::Physics3DRigidBody::setGravity)
        .member_function("getGravity", &ax::Physics3DRigidBody::getGravity)
        .member_function("setInvInertiaDiagLocal", &ax::Physics3DRigidBody::setInvInertiaDiagLocal)
        .member_function("getInvInertiaDiagLocal", &ax::Physics3DRigidBody::getInvInertiaDiagLocal)
        .member_function("setMassProps", &ax::Physics3DRigidBody::setMassProps)
        .member_function("getInvMass", &ax::Physics3DRigidBody::getInvMass)
        .member_function("getTotalForce", &ax::Physics3DRigidBody::getTotalForce)
        .member_function("getTotalTorque", &ax::Physics3DRigidBody::getTotalTorque)
        .member_function("setRestitution", &ax::Physics3DRigidBody::setRestitution)
        .member_function("getRestitution", &ax::Physics3DRigidBody::getRestitution)
        .member_function("setFriction", &ax::Physics3DRigidBody::setFriction)
        .member_function("getFriction", &ax::Physics3DRigidBody::getFriction)
        .member_function("setRollingFriction", &ax::Physics3DRigidBody::setRollingFriction)
        .member_function("getRollingFriction", &ax::Physics3DRigidBody::getRollingFriction)
        .member_function("setHitFraction", &ax::Physics3DRigidBody::setHitFraction)
        .member_function("getHitFraction", &ax::Physics3DRigidBody::getHitFraction)
        .member_function("setCcdMotionThreshold", &ax::Physics3DRigidBody::setCcdMotionThreshold)
        .member_function("getCcdMotionThreshold", &ax::Physics3DRigidBody::getCcdMotionThreshold)
        .member_function("setCcdSweptSphereRadius", &ax::Physics3DRigidBody::setCcdSweptSphereRadius)
        .member_function("getCcdSweptSphereRadius", &ax::Physics3DRigidBody::getCcdSweptSphereRadius)
        .member_function("setKinematic", &ax::Physics3DRigidBody::setKinematic)
        .member_function("isKinematic", &ax::Physics3DRigidBody::isKinematic)
        .member_function("getConstraint", &ax::Physics3DRigidBody::getConstraint)
        .member_function("getConstraintCount", &ax::Physics3DRigidBody::getConstraintCount)
        .member_function("setActive", &ax::Physics3DRigidBody::setActive)
        .member_function("init", &ax::Physics3DRigidBody::init)
        .member_function("addConstraint", &ax::Physics3DRigidBody::addConstraint)
        .member_function(
            "removeConstraint",
            [](ax::Physics3DRigidBody* self, unsigned int arg0) { self->removeConstraint(arg0); },
            [](ax::Physics3DRigidBody* self, ax::Physics3DConstraint* arg0) { self->removeConstraint(arg0); })
        .auto_wrap_objects(true);
    mod.class_("Physics3DRigidBody", class_Physics3DRigidBody);
}
static void js_register_ax_physics3d_Physics3DComponent(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Physics3DComponent> class_Physics3DComponent(isolate);
    class_Physics3DComponent.ctor([]() { return new ax::Physics3DComponent(); })
        .template inherit<ax::Component>()
        .member_function("setPhysics3DObject", &ax::Physics3DComponent::setPhysics3DObject)
        .member_function("getPhysics3DObject", &ax::Physics3DComponent::getPhysics3DObject)
        .member_function("addToPhysicsWorld", &ax::Physics3DComponent::addToPhysicsWorld)
        .member_function("setSyncFlag", &ax::Physics3DComponent::setSyncFlag)
        .member_function("syncNodeToPhysics", &ax::Physics3DComponent::syncNodeToPhysics)
        .member_function("syncPhysicsToNode", &ax::Physics3DComponent::syncPhysicsToNode)
        .static_function("getPhysics3DComponentName", &ax::Physics3DComponent::getPhysics3DComponentName)
        .auto_wrap_objects(true);
    mod.class_("Physics3DComponent", class_Physics3DComponent);
}
static void js_register_ax_physics3d_PhysicsMeshRenderer(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::PhysicsMeshRenderer> class_PhysicsMeshRenderer(isolate);
    class_PhysicsMeshRenderer.ctor([]() { return new ax::PhysicsMeshRenderer(); })
        .template inherit<ax::MeshRenderer>()
        .member_function("getPhysicsObj", &ax::PhysicsMeshRenderer::getPhysicsObj)
        .member_function("setSyncFlag", &ax::PhysicsMeshRenderer::setSyncFlag)
        .member_function("syncNodeToPhysics", &ax::PhysicsMeshRenderer::syncNodeToPhysics)
        .member_function("syncPhysicsToNode", &ax::PhysicsMeshRenderer::syncPhysicsToNode)
        .auto_wrap_objects(true);
    mod.class_("PhysicsMeshRenderer", class_PhysicsMeshRenderer);
}
static void js_register_ax_physics3d_Physics3DWorld(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Physics3DWorld> class_Physics3DWorld(isolate);
    class_Physics3DWorld.ctor([]() { return new ax::Physics3DWorld(); })
        .template inherit<ax::Object>()
        .member_function("setGravity", &ax::Physics3DWorld::setGravity)
        .member_function("getGravity", &ax::Physics3DWorld::getGravity)
        .member_function("addPhysics3DObject", &ax::Physics3DWorld::addPhysics3DObject)
        .member_function("removePhysics3DObject", &ax::Physics3DWorld::removePhysics3DObject)
        .member_function("removeAllPhysics3DObjects", &ax::Physics3DWorld::removeAllPhysics3DObjects)
        .member_function(
            "addPhysics3DConstraint",
            [](ax::Physics3DWorld* self, ax::Physics3DConstraint* arg0) { self->addPhysics3DConstraint(arg0); },
            [](ax::Physics3DWorld* self, ax::Physics3DConstraint* arg0, bool arg1) { self->addPhysics3DConstraint(arg0, arg1); })
        .member_function("removePhysics3DConstraint", &ax::Physics3DWorld::removePhysics3DConstraint)
        .member_function("removeAllPhysics3DConstraints", &ax::Physics3DWorld::removeAllPhysics3DConstraints)
        .member_function("stepSimulate", &ax::Physics3DWorld::stepSimulate)
        .member_function("setDebugDrawEnable", &ax::Physics3DWorld::setDebugDrawEnable)
        .member_function("isDebugDrawEnabled", &ax::Physics3DWorld::isDebugDrawEnabled)
        .member_function("debugDraw", &ax::Physics3DWorld::debugDraw)
        .member_function("collisionChecking", &ax::Physics3DWorld::collisionChecking)
        .member_function("needCollisionChecking", &ax::Physics3DWorld::needCollisionChecking)
        .member_function("setGhostPairCallback", &ax::Physics3DWorld::setGhostPairCallback)
        .auto_wrap_objects(true);
    mod.class_("Physics3DWorld", class_Physics3DWorld);
}
static void js_register_ax_physics3d_Physics3DConstraint(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Physics3DConstraint> class_Physics3DConstraint(isolate);
    class_Physics3DConstraint.template inherit<ax::Object>()
        .member_function("getBreakingImpulse", &ax::Physics3DConstraint::getBreakingImpulse)
        .member_function("setBreakingImpulse", &ax::Physics3DConstraint::setBreakingImpulse)
        .member_function("isEnabled", &ax::Physics3DConstraint::isEnabled)
        .member_function("setEnabled", &ax::Physics3DConstraint::setEnabled)
        .member_function("getBodyA", &ax::Physics3DConstraint::getBodyA)
        .member_function("getBodyB", &ax::Physics3DConstraint::getBodyB)
        .member_function("getConstraintType", &ax::Physics3DConstraint::getConstraintType)
        .member_function("getOverrideNumSolverIterations", &ax::Physics3DConstraint::getOverrideNumSolverIterations)
        .member_function("setOverrideNumSolverIterations", &ax::Physics3DConstraint::setOverrideNumSolverIterations)
        .member_function("getbtContraint", &ax::Physics3DConstraint::getbtContraint)
        .auto_wrap_objects(true);
    mod.class_("Physics3DConstraint", class_Physics3DConstraint);
}
static void js_register_ax_physics3d_Physics3DPointToPointConstraint(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Physics3DPointToPointConstraint> class_Physics3DPointToPointConstraint(isolate);
    class_Physics3DPointToPointConstraint.ctor([]() { return new ax::Physics3DPointToPointConstraint(); })
        .template inherit<ax::Physics3DConstraint>()
        .member_function("setPivotPointInA", &ax::Physics3DPointToPointConstraint::setPivotPointInA)
        .member_function("setPivotPointInB", &ax::Physics3DPointToPointConstraint::setPivotPointInB)
        .member_function("getPivotPointInA", &ax::Physics3DPointToPointConstraint::getPivotPointInA)
        .member_function("getPivotPointInB", &ax::Physics3DPointToPointConstraint::getPivotPointInB)
        .member_function(
            "init",
            [](ax::Physics3DPointToPointConstraint* self,
               ax::Physics3DRigidBody* arg0,
               ax::Physics3DRigidBody* arg1,
               ax::Vec3 arg2,
               ax::Vec3 arg3) { return self->init(arg0, arg1, arg2, arg3); },
            [](ax::Physics3DPointToPointConstraint* self, ax::Physics3DRigidBody* arg0, ax::Vec3 arg1) { return self->init(arg0, arg1); })
        .static_function(
            "create",
            [](ax::Physics3DRigidBody* arg0, ax::Physics3DRigidBody* arg1, ax::Vec3 arg2, ax::Vec3 arg3)
            { return ax::Physics3DPointToPointConstraint::create(arg0, arg1, arg2, arg3); },
            [](ax::Physics3DRigidBody* arg0, ax::Vec3 arg1) { return ax::Physics3DPointToPointConstraint::create(arg0, arg1); })
        .auto_wrap_objects(true);
    mod.class_("Physics3DPointToPointConstraint", class_Physics3DPointToPointConstraint);
}
static void js_register_ax_physics3d_Physics3DHingeConstraint(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Physics3DHingeConstraint> class_Physics3DHingeConstraint(isolate);
    class_Physics3DHingeConstraint.ctor([]() { return new ax::Physics3DHingeConstraint(); })
        .template inherit<ax::Physics3DConstraint>()
        .member_function("getFrameOffsetA", &ax::Physics3DHingeConstraint::getFrameOffsetA)
        .member_function("getFrameOffsetB", &ax::Physics3DHingeConstraint::getFrameOffsetB)
        .member_function("setFrames", &ax::Physics3DHingeConstraint::setFrames)
        .member_function("setAngularOnly", &ax::Physics3DHingeConstraint::setAngularOnly)
        .member_function("enableAngularMotor", &ax::Physics3DHingeConstraint::enableAngularMotor)
        .member_function("enableMotor", &ax::Physics3DHingeConstraint::enableMotor)
        .member_function("setMaxMotorImpulse", &ax::Physics3DHingeConstraint::setMaxMotorImpulse)
        .member_function(
            "setLimit",
            [](ax::Physics3DHingeConstraint* self, float arg0, float arg1) { self->setLimit(arg0, arg1); },
            [](ax::Physics3DHingeConstraint* self, float arg0, float arg1, float arg2) { self->setLimit(arg0, arg1, arg2); },
            [](ax::Physics3DHingeConstraint* self, float arg0, float arg1, float arg2, float arg3)
            { self->setLimit(arg0, arg1, arg2, arg3); },
            [](ax::Physics3DHingeConstraint* self, float arg0, float arg1, float arg2, float arg3, float arg4)
            { self->setLimit(arg0, arg1, arg2, arg3, arg4); })
        .member_function("setAxis", &ax::Physics3DHingeConstraint::setAxis)
        .member_function("getLowerLimit", &ax::Physics3DHingeConstraint::getLowerLimit)
        .member_function("getUpperLimit", &ax::Physics3DHingeConstraint::getUpperLimit)
        .member_function(
            "getHingeAngle",
            [](ax::Physics3DHingeConstraint* self, ax::Mat4 arg0, ax::Mat4 arg1) { return self->getHingeAngle(arg0, arg1); },
            [](ax::Physics3DHingeConstraint* self) { return self->getHingeAngle(); })
        .member_function("getAFrame", &ax::Physics3DHingeConstraint::getAFrame)
        .member_function("getBFrame", &ax::Physics3DHingeConstraint::getBFrame)
        .member_function("getAngularOnly", &ax::Physics3DHingeConstraint::getAngularOnly)
        .member_function("getEnableAngularMotor", &ax::Physics3DHingeConstraint::getEnableAngularMotor)
        .member_function("getMotorTargetVelosity", &ax::Physics3DHingeConstraint::getMotorTargetVelosity)
        .member_function("getMaxMotorImpulse", &ax::Physics3DHingeConstraint::getMaxMotorImpulse)
        .member_function("getUseFrameOffset", &ax::Physics3DHingeConstraint::getUseFrameOffset)
        .member_function("setUseFrameOffset", &ax::Physics3DHingeConstraint::setUseFrameOffset)
        .static_function(
            "create",
            [](ax::Physics3DRigidBody* arg0, ax::Vec3 arg1, ax::Vec3 arg2)
            { return ax::Physics3DHingeConstraint::create(arg0, arg1, arg2); },
            [](ax::Physics3DRigidBody* arg0, ax::Vec3 arg1, ax::Vec3 arg2, bool arg3)
            { return ax::Physics3DHingeConstraint::create(arg0, arg1, arg2, arg3); },
            [](ax::Physics3DRigidBody* arg0, ax::Mat4 arg1) { return ax::Physics3DHingeConstraint::create(arg0, arg1); },
            [](ax::Physics3DRigidBody* arg0, ax::Mat4 arg1, bool arg2) { return ax::Physics3DHingeConstraint::create(arg0, arg1, arg2); },
            [](ax::Physics3DRigidBody* arg0, ax::Physics3DRigidBody* arg1, ax::Vec3 arg2, ax::Vec3 arg3, ax::Vec3 arg4, ax::Vec3 arg5)
            { return ax::Physics3DHingeConstraint::create(arg0, arg1, arg2, arg3, arg4, arg5); },
            [](ax::Physics3DRigidBody* arg0,
               ax::Physics3DRigidBody* arg1,
               ax::Vec3 arg2,
               ax::Vec3 arg3,
               ax::Vec3 arg4,
               ax::Vec3 arg5,
               bool arg6) { return ax::Physics3DHingeConstraint::create(arg0, arg1, arg2, arg3, arg4, arg5, arg6); },
            [](ax::Physics3DRigidBody* arg0, ax::Physics3DRigidBody* arg1, ax::Mat4 arg2, ax::Mat4 arg3)
            { return ax::Physics3DHingeConstraint::create(arg0, arg1, arg2, arg3); },
            [](ax::Physics3DRigidBody* arg0, ax::Physics3DRigidBody* arg1, ax::Mat4 arg2, ax::Mat4 arg3, bool arg4)
            { return ax::Physics3DHingeConstraint::create(arg0, arg1, arg2, arg3, arg4); })
        .auto_wrap_objects(true);
    mod.class_("Physics3DHingeConstraint", class_Physics3DHingeConstraint);
}
static void js_register_ax_physics3d_Physics3DSliderConstraint(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Physics3DSliderConstraint> class_Physics3DSliderConstraint(isolate);
    class_Physics3DSliderConstraint.ctor([]() { return new ax::Physics3DSliderConstraint(); })
        .template inherit<ax::Physics3DConstraint>()
        .member_function("getFrameOffsetA", &ax::Physics3DSliderConstraint::getFrameOffsetA)
        .member_function("getFrameOffsetB", &ax::Physics3DSliderConstraint::getFrameOffsetB)
        .member_function("getLowerLinLimit", &ax::Physics3DSliderConstraint::getLowerLinLimit)
        .member_function("setLowerLinLimit", &ax::Physics3DSliderConstraint::setLowerLinLimit)
        .member_function("getUpperLinLimit", &ax::Physics3DSliderConstraint::getUpperLinLimit)
        .member_function("setUpperLinLimit", &ax::Physics3DSliderConstraint::setUpperLinLimit)
        .member_function("getLowerAngLimit", &ax::Physics3DSliderConstraint::getLowerAngLimit)
        .member_function("setLowerAngLimit", &ax::Physics3DSliderConstraint::setLowerAngLimit)
        .member_function("getUpperAngLimit", &ax::Physics3DSliderConstraint::getUpperAngLimit)
        .member_function("setUpperAngLimit", &ax::Physics3DSliderConstraint::setUpperAngLimit)
        .member_function("getUseLinearReferenceFrameA", &ax::Physics3DSliderConstraint::getUseLinearReferenceFrameA)
        .member_function("getSoftnessDirLin", &ax::Physics3DSliderConstraint::getSoftnessDirLin)
        .member_function("getRestitutionDirLin", &ax::Physics3DSliderConstraint::getRestitutionDirLin)
        .member_function("getDampingDirLin", &ax::Physics3DSliderConstraint::getDampingDirLin)
        .member_function("getSoftnessDirAng", &ax::Physics3DSliderConstraint::getSoftnessDirAng)
        .member_function("getRestitutionDirAng", &ax::Physics3DSliderConstraint::getRestitutionDirAng)
        .member_function("getDampingDirAng", &ax::Physics3DSliderConstraint::getDampingDirAng)
        .member_function("getSoftnessLimLin", &ax::Physics3DSliderConstraint::getSoftnessLimLin)
        .member_function("getRestitutionLimLin", &ax::Physics3DSliderConstraint::getRestitutionLimLin)
        .member_function("getDampingLimLin", &ax::Physics3DSliderConstraint::getDampingLimLin)
        .member_function("getSoftnessLimAng", &ax::Physics3DSliderConstraint::getSoftnessLimAng)
        .member_function("getRestitutionLimAng", &ax::Physics3DSliderConstraint::getRestitutionLimAng)
        .member_function("getDampingLimAng", &ax::Physics3DSliderConstraint::getDampingLimAng)
        .member_function("getSoftnessOrthoLin", &ax::Physics3DSliderConstraint::getSoftnessOrthoLin)
        .member_function("getRestitutionOrthoLin", &ax::Physics3DSliderConstraint::getRestitutionOrthoLin)
        .member_function("getDampingOrthoLin", &ax::Physics3DSliderConstraint::getDampingOrthoLin)
        .member_function("getSoftnessOrthoAng", &ax::Physics3DSliderConstraint::getSoftnessOrthoAng)
        .member_function("getRestitutionOrthoAng", &ax::Physics3DSliderConstraint::getRestitutionOrthoAng)
        .member_function("getDampingOrthoAng", &ax::Physics3DSliderConstraint::getDampingOrthoAng)
        .member_function("setSoftnessDirLin", &ax::Physics3DSliderConstraint::setSoftnessDirLin)
        .member_function("setRestitutionDirLin", &ax::Physics3DSliderConstraint::setRestitutionDirLin)
        .member_function("setDampingDirLin", &ax::Physics3DSliderConstraint::setDampingDirLin)
        .member_function("setSoftnessDirAng", &ax::Physics3DSliderConstraint::setSoftnessDirAng)
        .member_function("setRestitutionDirAng", &ax::Physics3DSliderConstraint::setRestitutionDirAng)
        .member_function("setDampingDirAng", &ax::Physics3DSliderConstraint::setDampingDirAng)
        .member_function("setSoftnessLimLin", &ax::Physics3DSliderConstraint::setSoftnessLimLin)
        .member_function("setRestitutionLimLin", &ax::Physics3DSliderConstraint::setRestitutionLimLin)
        .member_function("setDampingLimLin", &ax::Physics3DSliderConstraint::setDampingLimLin)
        .member_function("setSoftnessLimAng", &ax::Physics3DSliderConstraint::setSoftnessLimAng)
        .member_function("setRestitutionLimAng", &ax::Physics3DSliderConstraint::setRestitutionLimAng)
        .member_function("setDampingLimAng", &ax::Physics3DSliderConstraint::setDampingLimAng)
        .member_function("setSoftnessOrthoLin", &ax::Physics3DSliderConstraint::setSoftnessOrthoLin)
        .member_function("setRestitutionOrthoLin", &ax::Physics3DSliderConstraint::setRestitutionOrthoLin)
        .member_function("setDampingOrthoLin", &ax::Physics3DSliderConstraint::setDampingOrthoLin)
        .member_function("setSoftnessOrthoAng", &ax::Physics3DSliderConstraint::setSoftnessOrthoAng)
        .member_function("setRestitutionOrthoAng", &ax::Physics3DSliderConstraint::setRestitutionOrthoAng)
        .member_function("setDampingOrthoAng", &ax::Physics3DSliderConstraint::setDampingOrthoAng)
        .member_function("setPoweredLinMotor", &ax::Physics3DSliderConstraint::setPoweredLinMotor)
        .member_function("getPoweredLinMotor", &ax::Physics3DSliderConstraint::getPoweredLinMotor)
        .member_function("setTargetLinMotorVelocity", &ax::Physics3DSliderConstraint::setTargetLinMotorVelocity)
        .member_function("getTargetLinMotorVelocity", &ax::Physics3DSliderConstraint::getTargetLinMotorVelocity)
        .member_function("setMaxLinMotorForce", &ax::Physics3DSliderConstraint::setMaxLinMotorForce)
        .member_function("getMaxLinMotorForce", &ax::Physics3DSliderConstraint::getMaxLinMotorForce)
        .member_function("setPoweredAngMotor", &ax::Physics3DSliderConstraint::setPoweredAngMotor)
        .member_function("getPoweredAngMotor", &ax::Physics3DSliderConstraint::getPoweredAngMotor)
        .member_function("setTargetAngMotorVelocity", &ax::Physics3DSliderConstraint::setTargetAngMotorVelocity)
        .member_function("getTargetAngMotorVelocity", &ax::Physics3DSliderConstraint::getTargetAngMotorVelocity)
        .member_function("setMaxAngMotorForce", &ax::Physics3DSliderConstraint::setMaxAngMotorForce)
        .member_function("getMaxAngMotorForce", &ax::Physics3DSliderConstraint::getMaxAngMotorForce)
        .member_function("getLinearPos", &ax::Physics3DSliderConstraint::getLinearPos)
        .member_function("getAngularPos", &ax::Physics3DSliderConstraint::getAngularPos)
        .member_function("getUseFrameOffset", &ax::Physics3DSliderConstraint::getUseFrameOffset)
        .member_function("setUseFrameOffset", &ax::Physics3DSliderConstraint::setUseFrameOffset)
        .member_function("setFrames", &ax::Physics3DSliderConstraint::setFrames)
        .static_function("create", &ax::Physics3DSliderConstraint::create)
        .auto_wrap_objects(true);
    mod.class_("Physics3DSliderConstraint", class_Physics3DSliderConstraint);
}
static void js_register_ax_physics3d_Physics3DConeTwistConstraint(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Physics3DConeTwistConstraint> class_Physics3DConeTwistConstraint(isolate);
    class_Physics3DConeTwistConstraint.ctor([]() { return new ax::Physics3DConeTwistConstraint(); })
        .template inherit<ax::Physics3DConstraint>()
        .member_function(
            "setLimit",
            [](ax::Physics3DConeTwistConstraint* self, float arg0, float arg1, float arg2) { self->setLimit(arg0, arg1, arg2); },
            [](ax::Physics3DConeTwistConstraint* self, float arg0, float arg1, float arg2, float arg3)
            { self->setLimit(arg0, arg1, arg2, arg3); },
            [](ax::Physics3DConeTwistConstraint* self, float arg0, float arg1, float arg2, float arg3, float arg4)
            { self->setLimit(arg0, arg1, arg2, arg3, arg4); },
            [](ax::Physics3DConeTwistConstraint* self, float arg0, float arg1, float arg2, float arg3, float arg4, float arg5)
            { self->setLimit(arg0, arg1, arg2, arg3, arg4, arg5); })
        .member_function("getAFrame", &ax::Physics3DConeTwistConstraint::getAFrame)
        .member_function("getBFrame", &ax::Physics3DConeTwistConstraint::getBFrame)
        .member_function("getSwingSpan1", &ax::Physics3DConeTwistConstraint::getSwingSpan1)
        .member_function("getSwingSpan2", &ax::Physics3DConeTwistConstraint::getSwingSpan2)
        .member_function("getTwistSpan", &ax::Physics3DConeTwistConstraint::getTwistSpan)
        .member_function("getTwistAngle", &ax::Physics3DConeTwistConstraint::getTwistAngle)
        .member_function("setDamping", &ax::Physics3DConeTwistConstraint::setDamping)
        .member_function("enableMotor", &ax::Physics3DConeTwistConstraint::enableMotor)
        .member_function("setMaxMotorImpulse", &ax::Physics3DConeTwistConstraint::setMaxMotorImpulse)
        .member_function("setMaxMotorImpulseNormalized", &ax::Physics3DConeTwistConstraint::setMaxMotorImpulseNormalized)
        .member_function("getFixThresh", &ax::Physics3DConeTwistConstraint::getFixThresh)
        .member_function("setFixThresh", &ax::Physics3DConeTwistConstraint::setFixThresh)
        .member_function("GetPointForAngle", &ax::Physics3DConeTwistConstraint::GetPointForAngle)
        .member_function("setFrames", &ax::Physics3DConeTwistConstraint::setFrames)
        .member_function("getFrameOffsetA", &ax::Physics3DConeTwistConstraint::getFrameOffsetA)
        .member_function("getFrameOffsetB", &ax::Physics3DConeTwistConstraint::getFrameOffsetB)
        .static_function(
            "create",
            [](ax::Physics3DRigidBody* arg0, ax::Physics3DRigidBody* arg1, ax::Mat4 arg2, ax::Mat4 arg3)
            { return ax::Physics3DConeTwistConstraint::create(arg0, arg1, arg2, arg3); },
            [](ax::Physics3DRigidBody* arg0, ax::Mat4 arg1) { return ax::Physics3DConeTwistConstraint::create(arg0, arg1); })
        .auto_wrap_objects(true);
    mod.class_("Physics3DConeTwistConstraint", class_Physics3DConeTwistConstraint);
}
static void js_register_ax_physics3d_Physics3D6DofConstraint(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Physics3D6DofConstraint> class_Physics3D6DofConstraint(isolate);
    class_Physics3D6DofConstraint.ctor([]() { return new ax::Physics3D6DofConstraint(); })
        .template inherit<ax::Physics3DConstraint>()
        .member_function("setLinearLowerLimit", &ax::Physics3D6DofConstraint::setLinearLowerLimit)
        .member_function("getLinearLowerLimit", &ax::Physics3D6DofConstraint::getLinearLowerLimit)
        .member_function("setLinearUpperLimit", &ax::Physics3D6DofConstraint::setLinearUpperLimit)
        .member_function("getLinearUpperLimit", &ax::Physics3D6DofConstraint::getLinearUpperLimit)
        .member_function("setAngularLowerLimit", &ax::Physics3D6DofConstraint::setAngularLowerLimit)
        .member_function("getAngularLowerLimit", &ax::Physics3D6DofConstraint::getAngularLowerLimit)
        .member_function("setAngularUpperLimit", &ax::Physics3D6DofConstraint::setAngularUpperLimit)
        .member_function("getAngularUpperLimit", &ax::Physics3D6DofConstraint::getAngularUpperLimit)
        .member_function("isLimited", &ax::Physics3D6DofConstraint::isLimited)
        .member_function("getUseFrameOffset", &ax::Physics3D6DofConstraint::getUseFrameOffset)
        .member_function("setUseFrameOffset", &ax::Physics3D6DofConstraint::setUseFrameOffset)
        .static_function(
            "create",
            [](ax::Physics3DRigidBody* arg0, ax::Mat4 arg1, bool arg2) { return ax::Physics3D6DofConstraint::create(arg0, arg1, arg2); },
            [](ax::Physics3DRigidBody* arg0, ax::Physics3DRigidBody* arg1, ax::Mat4 arg2, ax::Mat4 arg3, bool arg4)
            { return ax::Physics3D6DofConstraint::create(arg0, arg1, arg2, arg3, arg4); })
        .auto_wrap_objects(true);
    mod.class_("Physics3D6DofConstraint", class_Physics3D6DofConstraint);
}
void js_register_all_ax_physics3d(JsRegistry& registry)
{
    v8pp::module& mod = registry.module("ax");
    js_register_ax_physics3d_Physics3DShape(mod);
    js_register_ax_physics3d_Physics3DObject(mod);
    js_register_ax_physics3d_Physics3DRigidBody(mod);
    js_register_ax_physics3d_Physics3DComponent(mod);
    js_register_ax_physics3d_PhysicsMeshRenderer(mod);
    js_register_ax_physics3d_Physics3DWorld(mod);
    js_register_ax_physics3d_Physics3DConstraint(mod);
    js_register_ax_physics3d_Physics3DPointToPointConstraint(mod);
    js_register_ax_physics3d_Physics3DHingeConstraint(mod);
    js_register_ax_physics3d_Physics3DSliderConstraint(mod);
    js_register_ax_physics3d_Physics3DConeTwistConstraint(mod);
    js_register_ax_physics3d_Physics3D6DofConstraint(mod);
}
#endif
