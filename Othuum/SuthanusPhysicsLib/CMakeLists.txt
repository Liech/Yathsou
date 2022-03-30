set(PROJECT_NAME SuthanusPhysicsLib)

################################################################################
# Source groups
################################################################################
set(Headerdateien
    "ArtilleryAim.h"
    "PhysicEngine.h"
    "PhysicNavigationMesh.h"
    "VehicleDriver.h"
)
source_group("Headerdateien" FILES ${Headerdateien})

set(Headerdateien__Objects
    "Objects/Box.h"
    "Objects/BoxBullet.h"
    "Objects/BulletCore.h"
    "Objects/HeightMap.cpp"
    "Objects/HeightMap.h"
    "Objects/HeightMapBullet.h"
    "Objects/PhysicObject.h"
    "Objects/Sphere.h"
    "Objects/SphereBullet.h"
    "Objects/Vehicle.cpp"
    "Objects/Vehicle.h"
    "Objects/VehicleBulletRaycast.h"
)
source_group("Headerdateien\\Objects" FILES ${Headerdateien__Objects})

set(Quelldateien
    "ArtilleryAim.cpp"
    "PhysicEngine.cpp"
    "PhysicNavigationMesh.cpp"
    "VehicleDriver.cpp"
)
source_group("Quelldateien" FILES ${Quelldateien})

set(Quelldateien__Objects
    "Objects/Box.cpp"
    "Objects/BoxBullet.cpp"
    "Objects/BulletCore.cpp"
    "Objects/HeightMapBullet.cpp"
    "Objects/PhysicObject.cpp"
    "Objects/Sphere.cpp"
    "Objects/SphereBullet.cpp"
    "Objects/VehicleBulletRaycast.cpp"
)
source_group("Quelldateien\\Objects" FILES ${Quelldateien__Objects})

set(bullet__Bullet3Collision__BroadPhaseCollision
    "lib/bullet/Bullet3Collision/BroadPhaseCollision/b3BroadphaseCallback.h"
    "lib/bullet/Bullet3Collision/BroadPhaseCollision/b3DynamicBvh.h"
    "lib/bullet/Bullet3Collision/BroadPhaseCollision/b3DynamicBvhBroadphase.h"
    "lib/bullet/Bullet3Collision/BroadPhaseCollision/b3OverlappingPair.h"
    "lib/bullet/Bullet3Collision/BroadPhaseCollision/b3OverlappingPairCache.h"
    "lib/bullet/Bullet3Collision/BroadPhaseCollision/shared/b3Aabb.h"
)
source_group("bullet\\Bullet3Collision\\BroadPhaseCollision" FILES ${bullet__Bullet3Collision__BroadPhaseCollision})

set(bullet__Bullet3Collision__NarrowPhaseCollision
    "lib/bullet/Bullet3Collision/NarrowPhaseCollision/b3Config.h"
    "lib/bullet/Bullet3Collision/NarrowPhaseCollision/b3Contact4.h"
    "lib/bullet/Bullet3Collision/NarrowPhaseCollision/b3ConvexUtility.h"
    "lib/bullet/Bullet3Collision/NarrowPhaseCollision/b3CpuNarrowPhase.h"
    "lib/bullet/Bullet3Collision/NarrowPhaseCollision/b3RaycastInfo.h"
    "lib/bullet/Bullet3Collision/NarrowPhaseCollision/b3RigidBodyCL.h"
    "lib/bullet/Bullet3Collision/NarrowPhaseCollision/shared/b3BvhSubtreeInfoData.h"
    "lib/bullet/Bullet3Collision/NarrowPhaseCollision/shared/b3BvhTraversal.h"
    "lib/bullet/Bullet3Collision/NarrowPhaseCollision/shared/b3ClipFaces.h"
    "lib/bullet/Bullet3Collision/NarrowPhaseCollision/shared/b3Collidable.h"
    "lib/bullet/Bullet3Collision/NarrowPhaseCollision/shared/b3Contact4Data.h"
    "lib/bullet/Bullet3Collision/NarrowPhaseCollision/shared/b3ContactConvexConvexSAT.h"
    "lib/bullet/Bullet3Collision/NarrowPhaseCollision/shared/b3ContactSphereSphere.h"
    "lib/bullet/Bullet3Collision/NarrowPhaseCollision/shared/b3ConvexPolyhedronData.h"
    "lib/bullet/Bullet3Collision/NarrowPhaseCollision/shared/b3FindConcaveSatAxis.h"
    "lib/bullet/Bullet3Collision/NarrowPhaseCollision/shared/b3FindSeparatingAxis.h"
    "lib/bullet/Bullet3Collision/NarrowPhaseCollision/shared/b3MprPenetration.h"
    "lib/bullet/Bullet3Collision/NarrowPhaseCollision/shared/b3NewContactReduction.h"
    "lib/bullet/Bullet3Collision/NarrowPhaseCollision/shared/b3QuantizedBvhNodeData.h"
    "lib/bullet/Bullet3Collision/NarrowPhaseCollision/shared/b3ReduceContacts.h"
    "lib/bullet/Bullet3Collision/NarrowPhaseCollision/shared/b3RigidBodyData.h"
    "lib/bullet/Bullet3Collision/NarrowPhaseCollision/shared/b3UpdateAabbs.h"
)
source_group("bullet\\Bullet3Collision\\NarrowPhaseCollision" FILES ${bullet__Bullet3Collision__NarrowPhaseCollision})

set(bullet__Bullet3Common
    "lib/bullet/Bullet3Common/b3AlignedAllocator.h"
    "lib/bullet/Bullet3Common/b3AlignedObjectArray.h"
    "lib/bullet/Bullet3Common/b3CommandLineArgs.h"
    "lib/bullet/Bullet3Common/b3FileUtils.h"
    "lib/bullet/Bullet3Common/b3HashMap.h"
    "lib/bullet/Bullet3Common/b3Logging.h"
    "lib/bullet/Bullet3Common/b3Matrix3x3.h"
    "lib/bullet/Bullet3Common/b3MinMax.h"
    "lib/bullet/Bullet3Common/b3PoolAllocator.h"
    "lib/bullet/Bullet3Common/b3QuadWord.h"
    "lib/bullet/Bullet3Common/b3Quaternion.h"
    "lib/bullet/Bullet3Common/b3Random.h"
    "lib/bullet/Bullet3Common/b3ResizablePool.h"
    "lib/bullet/Bullet3Common/b3Scalar.h"
    "lib/bullet/Bullet3Common/b3StackAlloc.h"
    "lib/bullet/Bullet3Common/b3Transform.h"
    "lib/bullet/Bullet3Common/b3TransformUtil.h"
    "lib/bullet/Bullet3Common/b3Vector3.h"
    "lib/bullet/Bullet3Common/shared/b3Float4.h"
    "lib/bullet/Bullet3Common/shared/b3Int2.h"
    "lib/bullet/Bullet3Common/shared/b3Int4.h"
    "lib/bullet/Bullet3Common/shared/b3Mat3x3.h"
    "lib/bullet/Bullet3Common/shared/b3PlatformDefinitions.h"
    "lib/bullet/Bullet3Common/shared/b3Quat.h"
)
source_group("bullet\\Bullet3Common" FILES ${bullet__Bullet3Common})

set(bullet__Bullet3Dynamics
    "lib/bullet/Bullet3Dynamics/b3CpuRigidBodyPipeline.h"
    "lib/bullet/Bullet3Dynamics/ConstraintSolver/b3ContactSolverInfo.h"
    "lib/bullet/Bullet3Dynamics/ConstraintSolver/b3FixedConstraint.h"
    "lib/bullet/Bullet3Dynamics/ConstraintSolver/b3Generic6DofConstraint.h"
    "lib/bullet/Bullet3Dynamics/ConstraintSolver/b3JacobianEntry.h"
    "lib/bullet/Bullet3Dynamics/ConstraintSolver/b3PgsJacobiSolver.h"
    "lib/bullet/Bullet3Dynamics/ConstraintSolver/b3Point2PointConstraint.h"
    "lib/bullet/Bullet3Dynamics/ConstraintSolver/b3SolverBody.h"
    "lib/bullet/Bullet3Dynamics/ConstraintSolver/b3SolverConstraint.h"
    "lib/bullet/Bullet3Dynamics/ConstraintSolver/b3TypedConstraint.h"
    "lib/bullet/Bullet3Dynamics/shared/b3ContactConstraint4.h"
    "lib/bullet/Bullet3Dynamics/shared/b3ConvertConstraint4.h"
    "lib/bullet/Bullet3Dynamics/shared/b3Inertia.h"
    "lib/bullet/Bullet3Dynamics/shared/b3IntegrateTransforms.h"
)
source_group("bullet\\Bullet3Dynamics" FILES ${bullet__Bullet3Dynamics})

set(bullet__Bullet3Geometry
    "lib/bullet/Bullet3Geometry/b3AabbUtil.h"
    "lib/bullet/Bullet3Geometry/b3ConvexHullComputer.h"
    "lib/bullet/Bullet3Geometry/b3GeometryUtil.h"
    "lib/bullet/Bullet3Geometry/b3GrahamScan2dConvexHull.h"
)
source_group("bullet\\Bullet3Geometry" FILES ${bullet__Bullet3Geometry})

set(bullet__Bullet3OpenCL
    "lib/bullet/Bullet3OpenCL/BroadphaseCollision/b3GpuBroadphaseInterface.h"
    "lib/bullet/Bullet3OpenCL/BroadphaseCollision/b3GpuGridBroadphase.h"
    "lib/bullet/Bullet3OpenCL/BroadphaseCollision/b3GpuParallelLinearBvh.h"
    "lib/bullet/Bullet3OpenCL/BroadphaseCollision/b3GpuParallelLinearBvhBroadphase.h"
    "lib/bullet/Bullet3OpenCL/BroadphaseCollision/b3GpuSapBroadphase.h"
    "lib/bullet/Bullet3OpenCL/BroadphaseCollision/b3SapAabb.h"
    "lib/bullet/Bullet3OpenCL/BroadphaseCollision/kernels/gridBroadphaseKernels.h"
    "lib/bullet/Bullet3OpenCL/BroadphaseCollision/kernels/parallelLinearBvhKernels.h"
    "lib/bullet/Bullet3OpenCL/BroadphaseCollision/kernels/sapKernels.h"
    "lib/bullet/Bullet3OpenCL/Initialize/b3OpenCLInclude.h"
    "lib/bullet/Bullet3OpenCL/Initialize/b3OpenCLUtils.h"
    "lib/bullet/Bullet3OpenCL/NarrowphaseCollision/b3BvhInfo.h"
    "lib/bullet/Bullet3OpenCL/NarrowphaseCollision/b3ContactCache.h"
    "lib/bullet/Bullet3OpenCL/NarrowphaseCollision/b3ConvexHullContact.h"
    "lib/bullet/Bullet3OpenCL/NarrowphaseCollision/b3ConvexPolyhedronCL.h"
    "lib/bullet/Bullet3OpenCL/NarrowphaseCollision/b3GjkEpa.h"
    "lib/bullet/Bullet3OpenCL/NarrowphaseCollision/b3OptimizedBvh.h"
    "lib/bullet/Bullet3OpenCL/NarrowphaseCollision/b3QuantizedBvh.h"
    "lib/bullet/Bullet3OpenCL/NarrowphaseCollision/b3StridingMeshInterface.h"
    "lib/bullet/Bullet3OpenCL/NarrowphaseCollision/b3SupportMappings.h"
    "lib/bullet/Bullet3OpenCL/NarrowphaseCollision/b3TriangleCallback.h"
    "lib/bullet/Bullet3OpenCL/NarrowphaseCollision/b3TriangleIndexVertexArray.h"
    "lib/bullet/Bullet3OpenCL/NarrowphaseCollision/b3VectorFloat4.h"
    "lib/bullet/Bullet3OpenCL/NarrowphaseCollision/b3VoronoiSimplexSolver.h"
    "lib/bullet/Bullet3OpenCL/NarrowphaseCollision/kernels/bvhTraversal.h"
    "lib/bullet/Bullet3OpenCL/NarrowphaseCollision/kernels/mprKernels.h"
    "lib/bullet/Bullet3OpenCL/NarrowphaseCollision/kernels/primitiveContacts.h"
    "lib/bullet/Bullet3OpenCL/NarrowphaseCollision/kernels/satClipHullContacts.h"
    "lib/bullet/Bullet3OpenCL/NarrowphaseCollision/kernels/satConcaveKernels.h"
    "lib/bullet/Bullet3OpenCL/NarrowphaseCollision/kernels/satKernels.h"
    "lib/bullet/Bullet3OpenCL/ParallelPrimitives/b3BoundSearchCL.h"
    "lib/bullet/Bullet3OpenCL/ParallelPrimitives/b3BufferInfoCL.h"
    "lib/bullet/Bullet3OpenCL/ParallelPrimitives/b3FillCL.h"
    "lib/bullet/Bullet3OpenCL/ParallelPrimitives/b3LauncherCL.h"
    "lib/bullet/Bullet3OpenCL/ParallelPrimitives/b3OpenCLArray.h"
    "lib/bullet/Bullet3OpenCL/ParallelPrimitives/b3PrefixScanCL.h"
    "lib/bullet/Bullet3OpenCL/ParallelPrimitives/b3PrefixScanFloat4CL.h"
    "lib/bullet/Bullet3OpenCL/ParallelPrimitives/b3RadixSort32CL.h"
    "lib/bullet/Bullet3OpenCL/ParallelPrimitives/kernels/BoundSearchKernelsCL.h"
    "lib/bullet/Bullet3OpenCL/ParallelPrimitives/kernels/CopyKernelsCL.h"
    "lib/bullet/Bullet3OpenCL/ParallelPrimitives/kernels/FillKernelsCL.h"
    "lib/bullet/Bullet3OpenCL/ParallelPrimitives/kernels/PrefixScanKernelsCL.h"
    "lib/bullet/Bullet3OpenCL/ParallelPrimitives/kernels/PrefixScanKernelsFloat4CL.h"
    "lib/bullet/Bullet3OpenCL/ParallelPrimitives/kernels/RadixSort32KernelsCL.h"
    "lib/bullet/Bullet3OpenCL/Raycast/b3GpuRaycast.h"
    "lib/bullet/Bullet3OpenCL/Raycast/kernels/rayCastKernels.h"
    "lib/bullet/Bullet3OpenCL/RigidBody/b3GpuConstraint4.h"
    "lib/bullet/Bullet3OpenCL/RigidBody/b3GpuGenericConstraint.h"
    "lib/bullet/Bullet3OpenCL/RigidBody/b3GpuJacobiContactSolver.h"
    "lib/bullet/Bullet3OpenCL/RigidBody/b3GpuNarrowPhase.h"
    "lib/bullet/Bullet3OpenCL/RigidBody/b3GpuNarrowPhaseInternalData.h"
    "lib/bullet/Bullet3OpenCL/RigidBody/b3GpuPgsConstraintSolver.h"
    "lib/bullet/Bullet3OpenCL/RigidBody/b3GpuPgsContactSolver.h"
    "lib/bullet/Bullet3OpenCL/RigidBody/b3GpuRigidBodyPipeline.h"
    "lib/bullet/Bullet3OpenCL/RigidBody/b3GpuRigidBodyPipelineInternalData.h"
    "lib/bullet/Bullet3OpenCL/RigidBody/b3GpuSolverBody.h"
    "lib/bullet/Bullet3OpenCL/RigidBody/b3GpuSolverConstraint.h"
    "lib/bullet/Bullet3OpenCL/RigidBody/b3Solver.h"
    "lib/bullet/Bullet3OpenCL/RigidBody/kernels/batchingKernels.h"
    "lib/bullet/Bullet3OpenCL/RigidBody/kernels/batchingKernelsNew.h"
    "lib/bullet/Bullet3OpenCL/RigidBody/kernels/integrateKernel.h"
    "lib/bullet/Bullet3OpenCL/RigidBody/kernels/jointSolver.h"
    "lib/bullet/Bullet3OpenCL/RigidBody/kernels/solveContact.h"
    "lib/bullet/Bullet3OpenCL/RigidBody/kernels/solveFriction.h"
    "lib/bullet/Bullet3OpenCL/RigidBody/kernels/solverSetup.h"
    "lib/bullet/Bullet3OpenCL/RigidBody/kernels/solverSetup2.h"
    "lib/bullet/Bullet3OpenCL/RigidBody/kernels/solverUtils.h"
    "lib/bullet/Bullet3OpenCL/RigidBody/kernels/updateAabbsKernel.h"
)
source_group("bullet\\Bullet3OpenCL" FILES ${bullet__Bullet3OpenCL})

set(bullet__Bullet3Serialize
    "lib/bullet/Bullet3Serialize/Bullet2FileLoader/autogenerated/bullet2.h"
    "lib/bullet/Bullet3Serialize/Bullet2FileLoader/b3BulletFile.h"
    "lib/bullet/Bullet3Serialize/Bullet2FileLoader/b3Chunk.h"
    "lib/bullet/Bullet3Serialize/Bullet2FileLoader/b3Common.h"
    "lib/bullet/Bullet3Serialize/Bullet2FileLoader/b3Defines.h"
    "lib/bullet/Bullet3Serialize/Bullet2FileLoader/b3DNA.h"
    "lib/bullet/Bullet3Serialize/Bullet2FileLoader/b3File.h"
    "lib/bullet/Bullet3Serialize/Bullet2FileLoader/b3Serializer.h"
)
source_group("bullet\\Bullet3Serialize" FILES ${bullet__Bullet3Serialize})

set(bullet__BulletCollision__BroadphaseCollision
    "lib/bullet/BulletCollision/BroadphaseCollision/btAxisSweep3.h"
    "lib/bullet/BulletCollision/BroadphaseCollision/btAxisSweep3Internal.h"
    "lib/bullet/BulletCollision/BroadphaseCollision/btBroadphaseInterface.h"
    "lib/bullet/BulletCollision/BroadphaseCollision/btBroadphaseProxy.h"
    "lib/bullet/BulletCollision/BroadphaseCollision/btCollisionAlgorithm.h"
    "lib/bullet/BulletCollision/BroadphaseCollision/btDbvt.h"
    "lib/bullet/BulletCollision/BroadphaseCollision/btDbvtBroadphase.h"
    "lib/bullet/BulletCollision/BroadphaseCollision/btDispatcher.h"
    "lib/bullet/BulletCollision/BroadphaseCollision/btOverlappingPairCache.h"
    "lib/bullet/BulletCollision/BroadphaseCollision/btOverlappingPairCallback.h"
    "lib/bullet/BulletCollision/BroadphaseCollision/btQuantizedBvh.h"
    "lib/bullet/BulletCollision/BroadphaseCollision/btSimpleBroadphase.h"
)
source_group("bullet\\BulletCollision\\BroadphaseCollision" FILES ${bullet__BulletCollision__BroadphaseCollision})

set(bullet__BulletCollision__CollisionDispatch
    "lib/bullet/BulletCollision/CollisionDispatch/btActivatingCollisionAlgorithm.h"
    "lib/bullet/BulletCollision/CollisionDispatch/btBox2dBox2dCollisionAlgorithm.h"
    "lib/bullet/BulletCollision/CollisionDispatch/btBoxBoxCollisionAlgorithm.h"
    "lib/bullet/BulletCollision/CollisionDispatch/btBoxBoxDetector.h"
    "lib/bullet/BulletCollision/CollisionDispatch/btCollisionConfiguration.h"
    "lib/bullet/BulletCollision/CollisionDispatch/btCollisionCreateFunc.h"
    "lib/bullet/BulletCollision/CollisionDispatch/btCollisionDispatcher.h"
    "lib/bullet/BulletCollision/CollisionDispatch/btCollisionDispatcherMt.h"
    "lib/bullet/BulletCollision/CollisionDispatch/btCollisionObject.h"
    "lib/bullet/BulletCollision/CollisionDispatch/btCollisionObjectWrapper.h"
    "lib/bullet/BulletCollision/CollisionDispatch/btCollisionWorld.h"
    "lib/bullet/BulletCollision/CollisionDispatch/btCollisionWorldImporter.h"
    "lib/bullet/BulletCollision/CollisionDispatch/btCompoundCollisionAlgorithm.h"
    "lib/bullet/BulletCollision/CollisionDispatch/btCompoundCompoundCollisionAlgorithm.h"
    "lib/bullet/BulletCollision/CollisionDispatch/btConvex2dConvex2dAlgorithm.h"
    "lib/bullet/BulletCollision/CollisionDispatch/btConvexConcaveCollisionAlgorithm.h"
    "lib/bullet/BulletCollision/CollisionDispatch/btConvexConvexAlgorithm.h"
    "lib/bullet/BulletCollision/CollisionDispatch/btConvexPlaneCollisionAlgorithm.h"
    "lib/bullet/BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h"
    "lib/bullet/BulletCollision/CollisionDispatch/btEmptyCollisionAlgorithm.h"
    "lib/bullet/BulletCollision/CollisionDispatch/btGhostObject.h"
    "lib/bullet/BulletCollision/CollisionDispatch/btHashedSimplePairCache.h"
    "lib/bullet/BulletCollision/CollisionDispatch/btInternalEdgeUtility.h"
    "lib/bullet/BulletCollision/CollisionDispatch/btManifoldResult.h"
    "lib/bullet/BulletCollision/CollisionDispatch/btSimulationIslandManager.h"
    "lib/bullet/BulletCollision/CollisionDispatch/btSphereBoxCollisionAlgorithm.h"
    "lib/bullet/BulletCollision/CollisionDispatch/btSphereSphereCollisionAlgorithm.h"
    "lib/bullet/BulletCollision/CollisionDispatch/btSphereTriangleCollisionAlgorithm.h"
    "lib/bullet/BulletCollision/CollisionDispatch/btUnionFind.h"
    "lib/bullet/BulletCollision/CollisionDispatch/SphereTriangleDetector.h"
)
source_group("bullet\\BulletCollision\\CollisionDispatch" FILES ${bullet__BulletCollision__CollisionDispatch})

set(bullet__BulletCollision__CollisionShapes
    "lib/bullet/BulletCollision/CollisionShapes/btBox2dShape.h"
    "lib/bullet/BulletCollision/CollisionShapes/btBoxShape.h"
    "lib/bullet/BulletCollision/CollisionShapes/btBvhTriangleMeshShape.h"
    "lib/bullet/BulletCollision/CollisionShapes/btCapsuleShape.h"
    "lib/bullet/BulletCollision/CollisionShapes/btCollisionMargin.h"
    "lib/bullet/BulletCollision/CollisionShapes/btCollisionShape.h"
    "lib/bullet/BulletCollision/CollisionShapes/btCompoundShape.h"
    "lib/bullet/BulletCollision/CollisionShapes/btConcaveShape.h"
    "lib/bullet/BulletCollision/CollisionShapes/btConeShape.h"
    "lib/bullet/BulletCollision/CollisionShapes/btConvex2dShape.h"
    "lib/bullet/BulletCollision/CollisionShapes/btConvexHullShape.h"
    "lib/bullet/BulletCollision/CollisionShapes/btConvexInternalShape.h"
    "lib/bullet/BulletCollision/CollisionShapes/btConvexPointCloudShape.h"
    "lib/bullet/BulletCollision/CollisionShapes/btConvexPolyhedron.h"
    "lib/bullet/BulletCollision/CollisionShapes/btConvexShape.h"
    "lib/bullet/BulletCollision/CollisionShapes/btConvexTriangleMeshShape.h"
    "lib/bullet/BulletCollision/CollisionShapes/btCylinderShape.h"
    "lib/bullet/BulletCollision/CollisionShapes/btEmptyShape.h"
    "lib/bullet/BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h"
    "lib/bullet/BulletCollision/CollisionShapes/btMaterial.h"
    "lib/bullet/BulletCollision/CollisionShapes/btMiniSDF.h"
    "lib/bullet/BulletCollision/CollisionShapes/btMinkowskiSumShape.h"
    "lib/bullet/BulletCollision/CollisionShapes/btMultimaterialTriangleMeshShape.h"
    "lib/bullet/BulletCollision/CollisionShapes/btMultiSphereShape.h"
    "lib/bullet/BulletCollision/CollisionShapes/btOptimizedBvh.h"
    "lib/bullet/BulletCollision/CollisionShapes/btPolyhedralConvexShape.h"
    "lib/bullet/BulletCollision/CollisionShapes/btScaledBvhTriangleMeshShape.h"
    "lib/bullet/BulletCollision/CollisionShapes/btSdfCollisionShape.h"
    "lib/bullet/BulletCollision/CollisionShapes/btShapeHull.h"
    "lib/bullet/BulletCollision/CollisionShapes/btSphereShape.h"
    "lib/bullet/BulletCollision/CollisionShapes/btStaticPlaneShape.h"
    "lib/bullet/BulletCollision/CollisionShapes/btStridingMeshInterface.h"
    "lib/bullet/BulletCollision/CollisionShapes/btTetrahedronShape.h"
    "lib/bullet/BulletCollision/CollisionShapes/btTriangleBuffer.h"
    "lib/bullet/BulletCollision/CollisionShapes/btTriangleCallback.h"
    "lib/bullet/BulletCollision/CollisionShapes/btTriangleIndexVertexArray.h"
    "lib/bullet/BulletCollision/CollisionShapes/btTriangleIndexVertexMaterialArray.h"
    "lib/bullet/BulletCollision/CollisionShapes/btTriangleInfoMap.h"
    "lib/bullet/BulletCollision/CollisionShapes/btTriangleMesh.h"
    "lib/bullet/BulletCollision/CollisionShapes/btTriangleMeshShape.h"
    "lib/bullet/BulletCollision/CollisionShapes/btTriangleShape.h"
    "lib/bullet/BulletCollision/CollisionShapes/btUniformScalingShape.h"
)
source_group("bullet\\BulletCollision\\CollisionShapes" FILES ${bullet__BulletCollision__CollisionShapes})

set(bullet__BulletCollision__Gimpact
    "lib/bullet/BulletCollision/Gimpact/btBoxCollision.h"
    "lib/bullet/BulletCollision/Gimpact/btClipPolygon.h"
    "lib/bullet/BulletCollision/Gimpact/btCompoundFromGimpact.h"
    "lib/bullet/BulletCollision/Gimpact/btContactProcessing.h"
    "lib/bullet/BulletCollision/Gimpact/btContactProcessingStructs.h"
    "lib/bullet/BulletCollision/Gimpact/btGenericPoolAllocator.h"
    "lib/bullet/BulletCollision/Gimpact/btGeometryOperations.h"
    "lib/bullet/BulletCollision/Gimpact/btGImpactBvh.h"
    "lib/bullet/BulletCollision/Gimpact/btGImpactBvhStructs.h"
    "lib/bullet/BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h"
    "lib/bullet/BulletCollision/Gimpact/btGImpactMassUtil.h"
    "lib/bullet/BulletCollision/Gimpact/btGImpactQuantizedBvh.h"
    "lib/bullet/BulletCollision/Gimpact/btGImpactQuantizedBvhStructs.h"
    "lib/bullet/BulletCollision/Gimpact/btGImpactShape.h"
    "lib/bullet/BulletCollision/Gimpact/btQuantization.h"
    "lib/bullet/BulletCollision/Gimpact/btTriangleShapeEx.h"
    "lib/bullet/BulletCollision/Gimpact/gim_array.h"
    "lib/bullet/BulletCollision/Gimpact/gim_basic_geometry_operations.h"
    "lib/bullet/BulletCollision/Gimpact/gim_bitset.h"
    "lib/bullet/BulletCollision/Gimpact/gim_box_collision.h"
    "lib/bullet/BulletCollision/Gimpact/gim_box_set.h"
    "lib/bullet/BulletCollision/Gimpact/gim_clip_polygon.h"
    "lib/bullet/BulletCollision/Gimpact/gim_contact.h"
    "lib/bullet/BulletCollision/Gimpact/gim_geom_types.h"
    "lib/bullet/BulletCollision/Gimpact/gim_geometry.h"
    "lib/bullet/BulletCollision/Gimpact/gim_hash_table.h"
    "lib/bullet/BulletCollision/Gimpact/gim_linear_math.h"
    "lib/bullet/BulletCollision/Gimpact/gim_math.h"
    "lib/bullet/BulletCollision/Gimpact/gim_memory.h"
    "lib/bullet/BulletCollision/Gimpact/gim_pair.h"
    "lib/bullet/BulletCollision/Gimpact/gim_radixsort.h"
    "lib/bullet/BulletCollision/Gimpact/gim_tri_collision.h"
    "lib/bullet/BulletCollision/NarrowPhaseCollision/btComputeGjkEpaPenetration.h"
    "lib/bullet/BulletCollision/NarrowPhaseCollision/btContinuousConvexCollision.h"
    "lib/bullet/BulletCollision/NarrowPhaseCollision/btConvexCast.h"
    "lib/bullet/BulletCollision/NarrowPhaseCollision/btConvexPenetrationDepthSolver.h"
    "lib/bullet/BulletCollision/NarrowPhaseCollision/btDiscreteCollisionDetectorInterface.h"
    "lib/bullet/BulletCollision/NarrowPhaseCollision/btGjkCollisionDescription.h"
    "lib/bullet/BulletCollision/NarrowPhaseCollision/btGjkConvexCast.h"
    "lib/bullet/BulletCollision/NarrowPhaseCollision/btGjkEpa2.h"
    "lib/bullet/BulletCollision/NarrowPhaseCollision/btGjkEpa3.h"
    "lib/bullet/BulletCollision/NarrowPhaseCollision/btGjkEpaPenetrationDepthSolver.h"
    "lib/bullet/BulletCollision/NarrowPhaseCollision/btGjkPairDetector.h"
    "lib/bullet/BulletCollision/NarrowPhaseCollision/btManifoldPoint.h"
    "lib/bullet/BulletCollision/NarrowPhaseCollision/btMinkowskiPenetrationDepthSolver.h"
    "lib/bullet/BulletCollision/NarrowPhaseCollision/btMprPenetration.h"
    "lib/bullet/BulletCollision/NarrowPhaseCollision/btPersistentManifold.h"
    "lib/bullet/BulletCollision/NarrowPhaseCollision/btPointCollector.h"
    "lib/bullet/BulletCollision/NarrowPhaseCollision/btPolyhedralContactClipping.h"
    "lib/bullet/BulletCollision/NarrowPhaseCollision/btRaycastCallback.h"
    "lib/bullet/BulletCollision/NarrowPhaseCollision/btSimplexSolverInterface.h"
    "lib/bullet/BulletCollision/NarrowPhaseCollision/btSubSimplexConvexCast.h"
    "lib/bullet/BulletCollision/NarrowPhaseCollision/btVoronoiSimplexSolver.h"
)
source_group("bullet\\BulletCollision\\Gimpact" FILES ${bullet__BulletCollision__Gimpact})

set(ALL_FILES
    ${Headerdateien}
    ${Headerdateien__Objects}
    ${Quelldateien}
    ${Quelldateien__Objects}
    ${bullet__Bullet3Collision__BroadPhaseCollision}
    ${bullet__Bullet3Collision__NarrowPhaseCollision}
    ${bullet__Bullet3Common}
    ${bullet__Bullet3Dynamics}
    ${bullet__Bullet3Geometry}
    ${bullet__Bullet3OpenCL}
    ${bullet__Bullet3Serialize}
    ${bullet__BulletCollision__BroadphaseCollision}
    ${bullet__BulletCollision__CollisionDispatch}
    ${bullet__BulletCollision__CollisionShapes}
    ${bullet__BulletCollision__Gimpact}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE SuthanusPhysicsLib)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE        "TRUE"
        INTERPROCEDURAL_OPTIMIZATION_RELEASEWITHDBG "TRUE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE        "TRUE"
        INTERPROCEDURAL_OPTIMIZATION_RELEASEWITHDBG "TRUE"
    )
endif()
################################################################################
# Include directories
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "$<$<CONFIG:Debug>:"
            "${CMAKE_CURRENT_SOURCE_DIR}/."
        ">"
        "$<$<CONFIG:Release>:"
            "${CMAKE_CURRENT_SOURCE_DIR}/lib/bullet/lib"
        ">"
        "$<$<CONFIG:ReleaseWithDbg>:"
            "${CMAKE_CURRENT_SOURCE_DIR}/lib/bullet/lib"
        ">"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/bullet;"
        "${CMAKE_CURRENT_SOURCE_DIR}/.."
    )
endif()

################################################################################
# Compile definitions
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG;"
            "BT_USE_DOUBLE_PRECISION"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG;"
            "BT_USE_DOUBLE_PRECISION"
        ">"
        "$<$<CONFIG:ReleaseWithDbg>:"
            "NDEBUG"
        ">"
        "_CONSOLE;"
        "UNICODE;"
        "_UNICODE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "$<$<CONFIG:ReleaseWithDbg>:"
            "NDEBUG"
        ">"
        "WIN32;"
        "_CONSOLE;"
        "UNICODE;"
        "_UNICODE"
    )
endif()

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /Oi;
                /Gy
            >
            $<$<CONFIG:ReleaseWithDbg>:
                /Oi;
                /Gy
            >
            /permissive-;
            /MP;
            /std:c++latest;
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING};
            /openmp
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /Oi;
                /Gy
            >
            $<$<CONFIG:ReleaseWithDbg>:
                /Oi;
                /Gy
            >
            /permissive-;
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    endif()
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF
            >
            $<$<CONFIG:ReleaseWithDbg>:
                /OPT:REF;
                /OPT:ICF
            >
            /SUBSYSTEM:CONSOLE
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /INCREMENTAL
            >
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF;
                /INCREMENTAL:NO
            >
            $<$<CONFIG:ReleaseWithDbg>:
                /OPT:REF;
                /OPT:ICF;
                /INCREMENTAL:NO
            >
            /DEBUG;
            /SUBSYSTEM:CONSOLE
        )
    endif()
endif()

################################################################################
# Dependencies
################################################################################
add_dependencies(${PROJECT_NAME}
    IyathuumCoreLib
)

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "$<$<CONFIG:Debug>:"
            "$(ProjectDir)lib/bullet/lib/gtest_vs2010_x64_debug;"
            "$(ProjectDir)lib/bullet/lib/BulletRobotics_vs2010_x64_debug;"
            "$(ProjectDir)lib/bullet/lib/ConvexDecomposition_vs2010_x64_debug;"
            "$(ProjectDir)lib/bullet/lib/BulletXmlWorldImporter_vs2010_x64_debug;"
            "$(ProjectDir)lib/bullet/lib/vhacd_vs2010_x64_debug;"
            "$(ProjectDir)lib/bullet/lib/HACD_vs2010_x64_debug;"
            "$(ProjectDir)lib/bullet/lib/Bullet2FileLoader_vs2010_x64_debug;"
            "$(ProjectDir)lib/bullet/lib/Bullet3OpenCL_clew_vs2010_x64_debug;"
            "$(ProjectDir)lib/bullet/lib/BulletCollision_vs2010_x64_debug;"
            "$(ProjectDir)lib/bullet/lib/Bullet3Dynamics_vs2010_x64_debug;"
            "$(ProjectDir)lib/bullet/lib/Bullet3Collision_vs2010_x64_debug;"
            "$(ProjectDir)lib/bullet/lib/Bullet3Geometry_vs2010_x64_debug;"
            "$(ProjectDir)lib/bullet/lib/BulletDynamics_vs2010_x64_debug;"
            "$(ProjectDir)lib/bullet/lib/LinearMath_vs2010_x64_debug;"
            "$(ProjectDir)lib/bullet/lib/BulletSoftBody_vs2010_x64_debug;"
            "$(ProjectDir)lib/bullet/lib/BulletInverseDynamics_vs2010_x64_debug;"
            "$(ProjectDir)lib/bullet/lib/BulletInverseDynamicsUtils_vs2010_x64_debug;"
            "$(ProjectDir)lib/bullet/lib/BulletWorldImporter_vs2010_x64_debug;"
            "$(ProjectDir)lib/bullet/lib/BulletFileLoader_vs2010_x64_debug;"
            "$(ProjectDir)lib/bullet/lib/BussIK_vs2010_x64_debug;"
            "$(ProjectDir)lib/bullet/lib/enet_vs2010_x64_debug;"
            "$(ProjectDir)lib/bullet/lib/Bullet3Common_vs2010_x64_debug;"
            "$(ProjectDir)lib/bullet/lib/clsocket_vs2010_x64_debug;"
            "$(ProjectDir)lib/bullet/lib/gwen_vs2010_x64_debug"
        ">"
        "$<$<CONFIG:Release>:"
            "$(ProjectDir)lib/bullet/lib/gtest_vs2010_x64_release;"
            "$(ProjectDir)lib/bullet/lib/BulletRobotics_vs2010_x64_release;"
            "$(ProjectDir)lib/bullet/lib/ConvexDecomposition_vs2010_x64_release;"
            "$(ProjectDir)lib/bullet/lib/BulletXmlWorldImporter_vs2010_x64_release;"
            "$(ProjectDir)lib/bullet/lib/vhacd_vs2010_x64_release;"
            "$(ProjectDir)lib/bullet/lib/HACD_vs2010_x64_release;"
            "$(ProjectDir)lib/bullet/lib/Bullet2FileLoader_vs2010_x64_release;"
            "$(ProjectDir)lib/bullet/lib/Bullet3OpenCL_clew_vs2010_x64_release;"
            "$(ProjectDir)lib/bullet/lib/BulletCollision_vs2010_x64_release;"
            "$(ProjectDir)lib/bullet/lib/Bullet3Dynamics_vs2010_x64_release;"
            "$(ProjectDir)lib/bullet/lib/Bullet3Collision_vs2010_x64_release;"
            "$(ProjectDir)lib/bullet/lib/Bullet3Geometry_vs2010_x64_release;"
            "$(ProjectDir)lib/bullet/lib/BulletDynamics_vs2010_x64_release;"
            "$(ProjectDir)lib/bullet/lib/LinearMath_vs2010_x64_release;"
            "$(ProjectDir)lib/bullet/lib/BulletSoftBody_vs2010_x64_release;"
            "$(ProjectDir)lib/bullet/lib/BulletInverseDynamics_vs2010_x64_release;"
            "$(ProjectDir)lib/bullet/lib/BulletInverseDynamicsUtils_vs2010_x64_release;"
            "$(ProjectDir)lib/bullet/lib/BulletWorldImporter_vs2010_x64_release;"
            "$(ProjectDir)lib/bullet/lib/BulletFileLoader_vs2010_x64_release;"
            "$(ProjectDir)lib/bullet/lib/BussIK_vs2010_x64_release;"
            "$(ProjectDir)lib/bullet/lib/enet_vs2010_x64_release;"
            "$(ProjectDir)lib/bullet/lib/Bullet3Common_vs2010_x64_release;"
            "$(ProjectDir)lib/bullet/lib/clsocket_vs2010_x64_release;"
            "$(ProjectDir)lib/bullet/lib/gwen_vs2010_x64_release"
        ">"
        "$<$<CONFIG:ReleaseWithDbg>:"
            "$(ProjectDir)lib/bullet/lib/Bullet2FileLoader;"
            "$(ProjectDir)lib/bullet/lib/Bullet3Collision;"
            "$(ProjectDir)lib/bullet/lib/Bullet3Common;"
            "$(ProjectDir)lib/bullet/lib/Bullet3Dynamics;"
            "$(ProjectDir)lib/bullet/lib/Bullet3Geometry;"
            "$(ProjectDir)lib/bullet/lib/Bullet3OpenCL_clew;"
            "$(ProjectDir)lib/bullet/lib/BulletCollision;"
            "$(ProjectDir)lib/bullet/lib/BulletDynamics;"
            "$(ProjectDir)lib/bullet/lib/BulletExampleBrowserLib;"
            "$(ProjectDir)lib/bullet/lib/BulletFileLoader;"
            "$(ProjectDir)lib/bullet/lib/BulletInverseDynamics;"
            "$(ProjectDir)lib/bullet/lib/BulletInverseDynamicsUtils;"
            "$(ProjectDir)lib/bullet/lib/BulletSoftBody;"
            "$(ProjectDir)lib/bullet/lib/BulletWorldImporter;"
            "$(ProjectDir)lib/bullet/lib/BulletXmlWorldImporter;"
            "$(ProjectDir)lib/bullet/lib/BussIK;"
            "$(ProjectDir)lib/bullet/lib/clsocket;"
            "$(ProjectDir)lib/bullet/lib/ConvexDecomposition;"
            "$(ProjectDir)lib/bullet/lib/GIMPACTUtils;"
            "$(ProjectDir)lib/bullet/lib/gtest;"
            "$(ProjectDir)lib/bullet/lib/gwen;"
            "$(ProjectDir)lib/bullet/lib/HACD;"
            "$(ProjectDir)lib/bullet/lib/LinearMath;"
            "$(ProjectDir)lib/bullet/lib/OpenGLWindow"
        ">"
    )
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

