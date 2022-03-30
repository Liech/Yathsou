set(PROJECT_NAME IyathuumCoreLib)

################################################################################
# Source groups
################################################################################
set(Header_Files
    "View2D.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Header_Files__BaseTypes
    "BaseTypes/AABB.h"
    "BaseTypes/Color.h"
    "BaseTypes/Command.h"
    "BaseTypes/glmAABB.h"
    "BaseTypes/Keys.h"
    "BaseTypes/Line.h"
    "BaseTypes/MultiDimensionalArray.h"
    "BaseTypes/Polygon.h"
    "BaseTypes/PolygonNet.h"
    "BaseTypes/Sound.h"
)
source_group("Header Files\\BaseTypes" FILES ${Header_Files__BaseTypes})

set(Header_Files__Mesh
    "Mesh/MarchingConvexPolygon.h"
    "Mesh/MarchingConvexPolygonNet.h"
)
source_group("Header Files\\Mesh" FILES ${Header_Files__Mesh})

set(Header_Files__Singleton
    "Singleton/Database.h"
    "Singleton/Factory.h"
)
source_group("Header Files\\Singleton" FILES ${Header_Files__Singleton})

set(Header_Files__Tree
    "Tree/Dijkstra.h"
    "Tree/glmOctree.h"
    "Tree/NMTree.h"
    "Tree/NMTreeDijkstra.h"
    "Tree/NMTreeNeighbourIndex.h"
    "Tree/NMTreeSpatialHash.h"
    "Tree/SpatialHash.h"
)
source_group("Header Files\\Tree" FILES ${Header_Files__Tree})

set(Header_Files__Util
    "Util/ConstExprHash.h"
    "Util/ContentLoader.h"
    "Util/Geometry.h"
    "Util/ImageSubsetUtil.h"
    "Util/ImageUtil.h"
    "Util/lambdaCapture2functionPointer.h"
    "Util/Scheduler.h"
    "Util/UpdateTimer.h"
)
source_group("Header Files\\Util" FILES ${Header_Files__Util})

set(Source_Files
    "View2D.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(Source_Files__BaseTypes
    "BaseTypes/AABB.cpp"
    "BaseTypes/Color.cpp"
    "BaseTypes/Key.cpp"
    "BaseTypes/Sound.cpp"
)
source_group("Source Files\\BaseTypes" FILES ${Source_Files__BaseTypes})

set(Source_Files__Tree
    "Tree/glmOctree.cpp"
)
source_group("Source Files\\Tree" FILES ${Source_Files__Tree})

set(Source_Files__Util
    "Util/ConstExprHash.cpp"
    "Util/ContentLoader.cpp"
    "Util/ImageSubsetUtil.cpp"
    "Util/ImageUtil.cpp"
    "Util/Scheduler.cpp"
    "Util/UpdateTimer.cpp"
)
source_group("Source Files\\Util" FILES ${Source_Files__Util})

set(lib__glm
    "lib/glm/CMakeLists.txt"
    "lib/glm/common.hpp"
    "lib/glm/detail/_features.hpp"
    "lib/glm/detail/_fixes.hpp"
    "lib/glm/detail/_noise.hpp"
    "lib/glm/detail/_swizzle.hpp"
    "lib/glm/detail/_swizzle_func.hpp"
    "lib/glm/detail/_vectorize.hpp"
    "lib/glm/detail/compute_common.hpp"
    "lib/glm/detail/compute_vector_relational.hpp"
    "lib/glm/detail/func_common.inl"
    "lib/glm/detail/func_common_simd.inl"
    "lib/glm/detail/func_exponential.inl"
    "lib/glm/detail/func_exponential_simd.inl"
    "lib/glm/detail/func_geometric.inl"
    "lib/glm/detail/func_geometric_simd.inl"
    "lib/glm/detail/func_integer.inl"
    "lib/glm/detail/func_integer_simd.inl"
    "lib/glm/detail/func_matrix.inl"
    "lib/glm/detail/func_matrix_simd.inl"
    "lib/glm/detail/func_packing.inl"
    "lib/glm/detail/func_packing_simd.inl"
    "lib/glm/detail/func_trigonometric.inl"
    "lib/glm/detail/func_trigonometric_simd.inl"
    "lib/glm/detail/func_vector_relational.inl"
    "lib/glm/detail/func_vector_relational_simd.inl"
    "lib/glm/detail/glm.cpp"
    "lib/glm/detail/qualifier.hpp"
    "lib/glm/detail/setup.hpp"
    "lib/glm/detail/type_float.hpp"
    "lib/glm/detail/type_half.hpp"
    "lib/glm/detail/type_half.inl"
    "lib/glm/detail/type_mat2x2.hpp"
    "lib/glm/detail/type_mat2x2.inl"
    "lib/glm/detail/type_mat2x3.hpp"
    "lib/glm/detail/type_mat2x3.inl"
    "lib/glm/detail/type_mat2x4.hpp"
    "lib/glm/detail/type_mat2x4.inl"
    "lib/glm/detail/type_mat3x2.hpp"
    "lib/glm/detail/type_mat3x2.inl"
    "lib/glm/detail/type_mat3x3.hpp"
    "lib/glm/detail/type_mat3x3.inl"
    "lib/glm/detail/type_mat3x4.hpp"
    "lib/glm/detail/type_mat3x4.inl"
    "lib/glm/detail/type_mat4x2.hpp"
    "lib/glm/detail/type_mat4x2.inl"
    "lib/glm/detail/type_mat4x3.hpp"
    "lib/glm/detail/type_mat4x3.inl"
    "lib/glm/detail/type_mat4x4.hpp"
    "lib/glm/detail/type_mat4x4.inl"
    "lib/glm/detail/type_mat4x4_simd.inl"
    "lib/glm/detail/type_quat.hpp"
    "lib/glm/detail/type_quat.inl"
    "lib/glm/detail/type_quat_simd.inl"
    "lib/glm/detail/type_vec1.hpp"
    "lib/glm/detail/type_vec1.inl"
    "lib/glm/detail/type_vec2.hpp"
    "lib/glm/detail/type_vec2.inl"
    "lib/glm/detail/type_vec3.hpp"
    "lib/glm/detail/type_vec3.inl"
    "lib/glm/detail/type_vec4.hpp"
    "lib/glm/detail/type_vec4.inl"
    "lib/glm/detail/type_vec4_simd.inl"
    "lib/glm/exponential.hpp"
    "lib/glm/ext.hpp"
    "lib/glm/ext/matrix_clip_space.hpp"
    "lib/glm/ext/matrix_clip_space.inl"
    "lib/glm/ext/matrix_common.hpp"
    "lib/glm/ext/matrix_common.inl"
    "lib/glm/ext/matrix_double2x2.hpp"
    "lib/glm/ext/matrix_double2x2_precision.hpp"
    "lib/glm/ext/matrix_double2x3.hpp"
    "lib/glm/ext/matrix_double2x3_precision.hpp"
    "lib/glm/ext/matrix_double2x4.hpp"
    "lib/glm/ext/matrix_double2x4_precision.hpp"
    "lib/glm/ext/matrix_double3x2.hpp"
    "lib/glm/ext/matrix_double3x2_precision.hpp"
    "lib/glm/ext/matrix_double3x3.hpp"
    "lib/glm/ext/matrix_double3x3_precision.hpp"
    "lib/glm/ext/matrix_double3x4.hpp"
    "lib/glm/ext/matrix_double3x4_precision.hpp"
    "lib/glm/ext/matrix_double4x2.hpp"
    "lib/glm/ext/matrix_double4x2_precision.hpp"
    "lib/glm/ext/matrix_double4x3.hpp"
    "lib/glm/ext/matrix_double4x3_precision.hpp"
    "lib/glm/ext/matrix_double4x4.hpp"
    "lib/glm/ext/matrix_double4x4_precision.hpp"
    "lib/glm/ext/matrix_float2x2.hpp"
    "lib/glm/ext/matrix_float2x2_precision.hpp"
    "lib/glm/ext/matrix_float2x3.hpp"
    "lib/glm/ext/matrix_float2x3_precision.hpp"
    "lib/glm/ext/matrix_float2x4.hpp"
    "lib/glm/ext/matrix_float2x4_precision.hpp"
    "lib/glm/ext/matrix_float3x2.hpp"
    "lib/glm/ext/matrix_float3x2_precision.hpp"
    "lib/glm/ext/matrix_float3x3.hpp"
    "lib/glm/ext/matrix_float3x3_precision.hpp"
    "lib/glm/ext/matrix_float3x4.hpp"
    "lib/glm/ext/matrix_float3x4_precision.hpp"
    "lib/glm/ext/matrix_float4x2.hpp"
    "lib/glm/ext/matrix_float4x2_precision.hpp"
    "lib/glm/ext/matrix_float4x3.hpp"
    "lib/glm/ext/matrix_float4x3_precision.hpp"
    "lib/glm/ext/matrix_float4x4.hpp"
    "lib/glm/ext/matrix_float4x4_precision.hpp"
    "lib/glm/ext/matrix_projection.hpp"
    "lib/glm/ext/matrix_projection.inl"
    "lib/glm/ext/matrix_relational.hpp"
    "lib/glm/ext/matrix_relational.inl"
    "lib/glm/ext/matrix_transform.hpp"
    "lib/glm/ext/matrix_transform.inl"
    "lib/glm/ext/quaternion_common.hpp"
    "lib/glm/ext/quaternion_common.inl"
    "lib/glm/ext/quaternion_common_simd.inl"
    "lib/glm/ext/quaternion_double.hpp"
    "lib/glm/ext/quaternion_double_precision.hpp"
    "lib/glm/ext/quaternion_exponential.hpp"
    "lib/glm/ext/quaternion_exponential.inl"
    "lib/glm/ext/quaternion_float.hpp"
    "lib/glm/ext/quaternion_float_precision.hpp"
    "lib/glm/ext/quaternion_geometric.hpp"
    "lib/glm/ext/quaternion_geometric.inl"
    "lib/glm/ext/quaternion_relational.hpp"
    "lib/glm/ext/quaternion_relational.inl"
    "lib/glm/ext/quaternion_transform.hpp"
    "lib/glm/ext/quaternion_transform.inl"
    "lib/glm/ext/quaternion_trigonometric.hpp"
    "lib/glm/ext/quaternion_trigonometric.inl"
    "lib/glm/ext/scalar_common.hpp"
    "lib/glm/ext/scalar_common.inl"
    "lib/glm/ext/scalar_constants.hpp"
    "lib/glm/ext/scalar_constants.inl"
    "lib/glm/ext/scalar_int_sized.hpp"
    "lib/glm/ext/scalar_relational.hpp"
    "lib/glm/ext/scalar_relational.inl"
    "lib/glm/ext/scalar_uint_sized.hpp"
    "lib/glm/ext/scalar_ulp.hpp"
    "lib/glm/ext/scalar_ulp.inl"
    "lib/glm/ext/vector_bool1.hpp"
    "lib/glm/ext/vector_bool1_precision.hpp"
    "lib/glm/ext/vector_bool2.hpp"
    "lib/glm/ext/vector_bool2_precision.hpp"
    "lib/glm/ext/vector_bool3.hpp"
    "lib/glm/ext/vector_bool3_precision.hpp"
    "lib/glm/ext/vector_bool4.hpp"
    "lib/glm/ext/vector_bool4_precision.hpp"
    "lib/glm/ext/vector_common.hpp"
    "lib/glm/ext/vector_common.inl"
    "lib/glm/ext/vector_double1.hpp"
    "lib/glm/ext/vector_double1_precision.hpp"
    "lib/glm/ext/vector_double2.hpp"
    "lib/glm/ext/vector_double2_precision.hpp"
    "lib/glm/ext/vector_double3.hpp"
    "lib/glm/ext/vector_double3_precision.hpp"
    "lib/glm/ext/vector_double4.hpp"
    "lib/glm/ext/vector_double4_precision.hpp"
    "lib/glm/ext/vector_float1.hpp"
    "lib/glm/ext/vector_float1_precision.hpp"
    "lib/glm/ext/vector_float2.hpp"
    "lib/glm/ext/vector_float2_precision.hpp"
    "lib/glm/ext/vector_float3.hpp"
    "lib/glm/ext/vector_float3_precision.hpp"
    "lib/glm/ext/vector_float4.hpp"
    "lib/glm/ext/vector_float4_precision.hpp"
    "lib/glm/ext/vector_int1.hpp"
    "lib/glm/ext/vector_int1_precision.hpp"
    "lib/glm/ext/vector_int2.hpp"
    "lib/glm/ext/vector_int2_precision.hpp"
    "lib/glm/ext/vector_int3.hpp"
    "lib/glm/ext/vector_int3_precision.hpp"
    "lib/glm/ext/vector_int4.hpp"
    "lib/glm/ext/vector_int4_precision.hpp"
    "lib/glm/ext/vector_packing.hpp"
    "lib/glm/ext/vector_packing.inl"
    "lib/glm/ext/vector_relational.hpp"
    "lib/glm/ext/vector_relational.inl"
    "lib/glm/ext/vector_uint1.hpp"
    "lib/glm/ext/vector_uint1_precision.hpp"
    "lib/glm/ext/vector_uint2.hpp"
    "lib/glm/ext/vector_uint2_precision.hpp"
    "lib/glm/ext/vector_uint3.hpp"
    "lib/glm/ext/vector_uint3_precision.hpp"
    "lib/glm/ext/vector_uint4.hpp"
    "lib/glm/ext/vector_uint4_precision.hpp"
    "lib/glm/ext/vector_ulp.hpp"
    "lib/glm/ext/vector_ulp.inl"
    "lib/glm/fwd.hpp"
    "lib/glm/geometric.hpp"
    "lib/glm/glm.hpp"
    "lib/glm/gtc/bitfield.hpp"
    "lib/glm/gtc/bitfield.inl"
    "lib/glm/gtc/color_space.hpp"
    "lib/glm/gtc/color_space.inl"
    "lib/glm/gtc/constants.hpp"
    "lib/glm/gtc/constants.inl"
    "lib/glm/gtc/epsilon.hpp"
    "lib/glm/gtc/epsilon.inl"
    "lib/glm/gtc/integer.hpp"
    "lib/glm/gtc/integer.inl"
    "lib/glm/gtc/matrix_access.hpp"
    "lib/glm/gtc/matrix_access.inl"
    "lib/glm/gtc/matrix_integer.hpp"
    "lib/glm/gtc/matrix_inverse.hpp"
    "lib/glm/gtc/matrix_inverse.inl"
    "lib/glm/gtc/matrix_transform.hpp"
    "lib/glm/gtc/matrix_transform.inl"
    "lib/glm/gtc/noise.hpp"
    "lib/glm/gtc/noise.inl"
    "lib/glm/gtc/packing.hpp"
    "lib/glm/gtc/packing.inl"
    "lib/glm/gtc/quaternion.hpp"
    "lib/glm/gtc/quaternion.inl"
    "lib/glm/gtc/quaternion_simd.inl"
    "lib/glm/gtc/random.hpp"
    "lib/glm/gtc/random.inl"
    "lib/glm/gtc/reciprocal.hpp"
    "lib/glm/gtc/reciprocal.inl"
    "lib/glm/gtc/round.hpp"
    "lib/glm/gtc/round.inl"
    "lib/glm/gtc/type_aligned.hpp"
    "lib/glm/gtc/type_precision.hpp"
    "lib/glm/gtc/type_precision.inl"
    "lib/glm/gtc/type_ptr.hpp"
    "lib/glm/gtc/type_ptr.inl"
    "lib/glm/gtc/ulp.hpp"
    "lib/glm/gtc/ulp.inl"
    "lib/glm/gtc/vec1.hpp"
    "lib/glm/gtx/associated_min_max.hpp"
    "lib/glm/gtx/associated_min_max.inl"
    "lib/glm/gtx/bit.hpp"
    "lib/glm/gtx/bit.inl"
    "lib/glm/gtx/closest_point.hpp"
    "lib/glm/gtx/closest_point.inl"
    "lib/glm/gtx/color_encoding.hpp"
    "lib/glm/gtx/color_encoding.inl"
    "lib/glm/gtx/color_space.hpp"
    "lib/glm/gtx/color_space.inl"
    "lib/glm/gtx/color_space_YCoCg.hpp"
    "lib/glm/gtx/color_space_YCoCg.inl"
    "lib/glm/gtx/common.hpp"
    "lib/glm/gtx/common.inl"
    "lib/glm/gtx/compatibility.hpp"
    "lib/glm/gtx/compatibility.inl"
    "lib/glm/gtx/component_wise.hpp"
    "lib/glm/gtx/component_wise.inl"
    "lib/glm/gtx/dual_quaternion.hpp"
    "lib/glm/gtx/dual_quaternion.inl"
    "lib/glm/gtx/easing.hpp"
    "lib/glm/gtx/easing.inl"
    "lib/glm/gtx/euler_angles.hpp"
    "lib/glm/gtx/euler_angles.inl"
    "lib/glm/gtx/extend.hpp"
    "lib/glm/gtx/extend.inl"
    "lib/glm/gtx/extended_min_max.hpp"
    "lib/glm/gtx/extended_min_max.inl"
    "lib/glm/gtx/exterior_product.hpp"
    "lib/glm/gtx/exterior_product.inl"
    "lib/glm/gtx/fast_exponential.hpp"
    "lib/glm/gtx/fast_exponential.inl"
    "lib/glm/gtx/fast_square_root.hpp"
    "lib/glm/gtx/fast_square_root.inl"
    "lib/glm/gtx/fast_trigonometry.hpp"
    "lib/glm/gtx/fast_trigonometry.inl"
    "lib/glm/gtx/float_notmalize.inl"
    "lib/glm/gtx/functions.hpp"
    "lib/glm/gtx/functions.inl"
    "lib/glm/gtx/gradient_paint.hpp"
    "lib/glm/gtx/gradient_paint.inl"
    "lib/glm/gtx/handed_coordinate_space.hpp"
    "lib/glm/gtx/handed_coordinate_space.inl"
    "lib/glm/gtx/hash.hpp"
    "lib/glm/gtx/hash.inl"
    "lib/glm/gtx/integer.hpp"
    "lib/glm/gtx/integer.inl"
    "lib/glm/gtx/intersect.hpp"
    "lib/glm/gtx/intersect.inl"
    "lib/glm/gtx/io.hpp"
    "lib/glm/gtx/io.inl"
    "lib/glm/gtx/log_base.hpp"
    "lib/glm/gtx/log_base.inl"
    "lib/glm/gtx/matrix_cross_product.hpp"
    "lib/glm/gtx/matrix_cross_product.inl"
    "lib/glm/gtx/matrix_decompose.hpp"
    "lib/glm/gtx/matrix_decompose.inl"
    "lib/glm/gtx/matrix_factorisation.hpp"
    "lib/glm/gtx/matrix_factorisation.inl"
    "lib/glm/gtx/matrix_interpolation.hpp"
    "lib/glm/gtx/matrix_interpolation.inl"
    "lib/glm/gtx/matrix_major_storage.hpp"
    "lib/glm/gtx/matrix_major_storage.inl"
    "lib/glm/gtx/matrix_operation.hpp"
    "lib/glm/gtx/matrix_operation.inl"
    "lib/glm/gtx/matrix_query.hpp"
    "lib/glm/gtx/matrix_query.inl"
    "lib/glm/gtx/matrix_transform_2d.hpp"
    "lib/glm/gtx/matrix_transform_2d.inl"
    "lib/glm/gtx/mixed_product.hpp"
    "lib/glm/gtx/mixed_product.inl"
    "lib/glm/gtx/norm.hpp"
    "lib/glm/gtx/norm.inl"
    "lib/glm/gtx/normal.hpp"
    "lib/glm/gtx/normal.inl"
    "lib/glm/gtx/normalize_dot.hpp"
    "lib/glm/gtx/normalize_dot.inl"
    "lib/glm/gtx/number_precision.hpp"
    "lib/glm/gtx/number_precision.inl"
    "lib/glm/gtx/optimum_pow.hpp"
    "lib/glm/gtx/optimum_pow.inl"
    "lib/glm/gtx/orthonormalize.hpp"
    "lib/glm/gtx/orthonormalize.inl"
    "lib/glm/gtx/perpendicular.hpp"
    "lib/glm/gtx/perpendicular.inl"
    "lib/glm/gtx/polar_coordinates.hpp"
    "lib/glm/gtx/polar_coordinates.inl"
    "lib/glm/gtx/projection.hpp"
    "lib/glm/gtx/projection.inl"
    "lib/glm/gtx/quaternion.hpp"
    "lib/glm/gtx/quaternion.inl"
    "lib/glm/gtx/range.hpp"
    "lib/glm/gtx/raw_data.hpp"
    "lib/glm/gtx/raw_data.inl"
    "lib/glm/gtx/rotate_normalized_axis.hpp"
    "lib/glm/gtx/rotate_normalized_axis.inl"
    "lib/glm/gtx/rotate_vector.hpp"
    "lib/glm/gtx/rotate_vector.inl"
    "lib/glm/gtx/scalar_multiplication.hpp"
    "lib/glm/gtx/scalar_relational.hpp"
    "lib/glm/gtx/scalar_relational.inl"
    "lib/glm/gtx/spline.hpp"
    "lib/glm/gtx/spline.inl"
    "lib/glm/gtx/std_based_type.hpp"
    "lib/glm/gtx/std_based_type.inl"
    "lib/glm/gtx/string_cast.hpp"
    "lib/glm/gtx/string_cast.inl"
    "lib/glm/gtx/texture.hpp"
    "lib/glm/gtx/texture.inl"
    "lib/glm/gtx/transform.hpp"
    "lib/glm/gtx/transform.inl"
    "lib/glm/gtx/transform2.hpp"
    "lib/glm/gtx/transform2.inl"
    "lib/glm/gtx/type_aligned.hpp"
    "lib/glm/gtx/type_aligned.inl"
    "lib/glm/gtx/type_trait.hpp"
    "lib/glm/gtx/type_trait.inl"
    "lib/glm/gtx/vec_swizzle.hpp"
    "lib/glm/gtx/vector_angle.hpp"
    "lib/glm/gtx/vector_angle.inl"
    "lib/glm/gtx/vector_query.hpp"
    "lib/glm/gtx/vector_query.inl"
    "lib/glm/gtx/wrap.hpp"
    "lib/glm/gtx/wrap.inl"
    "lib/glm/integer.hpp"
    "lib/glm/mat2x2.hpp"
    "lib/glm/mat2x3.hpp"
    "lib/glm/mat2x4.hpp"
    "lib/glm/mat3x2.hpp"
    "lib/glm/mat3x3.hpp"
    "lib/glm/mat3x4.hpp"
    "lib/glm/mat4x2.hpp"
    "lib/glm/mat4x3.hpp"
    "lib/glm/mat4x4.hpp"
    "lib/glm/matrix.hpp"
    "lib/glm/packing.hpp"
    "lib/glm/simd/common.h"
    "lib/glm/simd/exponential.h"
    "lib/glm/simd/geometric.h"
    "lib/glm/simd/integer.h"
    "lib/glm/simd/matrix.h"
    "lib/glm/simd/packing.h"
    "lib/glm/simd/platform.h"
    "lib/glm/simd/trigonometric.h"
    "lib/glm/simd/vector_relational.h"
    "lib/glm/trigonometric.hpp"
    "lib/glm/vec2.hpp"
    "lib/glm/vec3.hpp"
    "lib/glm/vec4.hpp"
    "lib/glm/vector_relational.hpp"
)
source_group("lib\\glm" FILES ${lib__glm})

set(ALL_FILES
    ${Header_Files}
    ${Header_Files__BaseTypes}
    ${Header_Files__Mesh}
    ${Header_Files__Singleton}
    ${Header_Files__Tree}
    ${Header_Files__Util}
    ${Source_Files}
    ${Source_Files__BaseTypes}
    ${Source_Files__Tree}
    ${Source_Files__Util}
    ${lib__glm}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE IyathuumCoreLib)

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
        "${CMAKE_CURRENT_SOURCE_DIR}/lib;"
        "${CMAKE_CURRENT_SOURCE_DIR}/.."
    )
endif()

################################################################################
# Compile definitions
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
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
                /MP;
                /Oi;
                /Gy;
                /openmp
            >
            $<$<CONFIG:ReleaseWithDbg>:
                /MP;
                /Oi;
                /Gy;
                /openmp
            >
            /permissive-;
            /std:c++latest;
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
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

