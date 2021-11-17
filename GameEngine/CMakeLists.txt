set(PROJECT_NAME GameEngine)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "res/shaders/lineFrag.shader"
    "res/shaders/lineVer.shader"
    "src/App/ClickHandler.cpp"
    "src/App/ClickHandler.h"
    "src/App/Layers/ComplexComponent.cpp"
    "src/App/Layers/ComplexComponent.h"
    "src/App/Layers/Component.cpp"
    "src/App/Layers/Component.h"
    "src/App/Layers/HUDLayer.cpp"
    "src/App/Layers/HUDLayer.h"
    "src/App/Layers/ILayer.h"
    "src/App/Layers/RectColoredComponent.cpp"
    "src/App/Layers/RectColoredComponent.h"
    "src/App/Layers/WorldLayer.cpp"
    "src/App/Layers/WorldLayer.h"
    "src/App/Layers/WorldLayers.cpp"
    "src/App/Layers/WorldLayers.h"
    "src/App/MouseState.cpp"
    "src/App/MouseState.h"
    "src/App/ObjectPicker.cpp"
    "src/App/ObjectPicker.h"
    "src/App/StencilDrawer.cpp"
    "src/App/StencilDrawer.h"
    "src/App/WorldGeneration/MapGenerator.cpp"
    "src/App/WorldGeneration/MapGenerator.h"
    "src/App/WorldGeneration/ObjectGenerator.cpp"
    "src/App/WorldGeneration/ObjectGenerator.h"
    "src/App/WorldGeneration/PoissonGenerator.cpp"
    "src/App/WorldGeneration/PoissonGenerator.h"
    "src/GE/ClassDiagram.cd"
    "src/GE/MousePosition.cpp"
)
source_group("" FILES ${no_group_source_files})

set(libs__glm
    "libs/glm/common.hpp"
    "libs/glm/exponential.hpp"
    "libs/glm/ext.hpp"
    "libs/glm/fwd.hpp"
    "libs/glm/geometric.hpp"
    "libs/glm/glm.hpp"
    "libs/glm/integer.hpp"
    "libs/glm/mat2x2.hpp"
    "libs/glm/mat2x3.hpp"
    "libs/glm/mat2x4.hpp"
    "libs/glm/mat3x2.hpp"
    "libs/glm/mat3x3.hpp"
    "libs/glm/mat3x4.hpp"
    "libs/glm/mat4x2.hpp"
    "libs/glm/mat4x3.hpp"
    "libs/glm/mat4x4.hpp"
    "libs/glm/matrix.hpp"
    "libs/glm/packing.hpp"
    "libs/glm/trigonometric.hpp"
    "libs/glm/vec2.hpp"
    "libs/glm/vec3.hpp"
    "libs/glm/vec4.hpp"
    "libs/glm/vector_relational.hpp"
)
source_group("libs\\glm" FILES ${libs__glm})

set(libs__glm__detail
    "libs/glm/detail/_features.hpp"
    "libs/glm/detail/_fixes.hpp"
    "libs/glm/detail/_noise.hpp"
    "libs/glm/detail/_swizzle.hpp"
    "libs/glm/detail/_swizzle_func.hpp"
    "libs/glm/detail/_vectorize.hpp"
    "libs/glm/detail/compute_common.hpp"
    "libs/glm/detail/compute_vector_relational.hpp"
    "libs/glm/detail/func_common.inl"
    "libs/glm/detail/func_common_simd.inl"
    "libs/glm/detail/func_exponential.inl"
    "libs/glm/detail/func_exponential_simd.inl"
    "libs/glm/detail/func_geometric.inl"
    "libs/glm/detail/func_geometric_simd.inl"
    "libs/glm/detail/func_integer.inl"
    "libs/glm/detail/func_integer_simd.inl"
    "libs/glm/detail/func_matrix.inl"
    "libs/glm/detail/func_matrix_simd.inl"
    "libs/glm/detail/func_packing.inl"
    "libs/glm/detail/func_packing_simd.inl"
    "libs/glm/detail/func_trigonometric.inl"
    "libs/glm/detail/func_trigonometric_simd.inl"
    "libs/glm/detail/func_vector_relational.inl"
    "libs/glm/detail/func_vector_relational_simd.inl"
    "libs/glm/detail/qualifier.hpp"
    "libs/glm/detail/setup.hpp"
    "libs/glm/detail/type_float.hpp"
    "libs/glm/detail/type_half.hpp"
    "libs/glm/detail/type_half.inl"
    "libs/glm/detail/type_mat2x2.hpp"
    "libs/glm/detail/type_mat2x2.inl"
    "libs/glm/detail/type_mat2x3.hpp"
    "libs/glm/detail/type_mat2x3.inl"
    "libs/glm/detail/type_mat2x4.hpp"
    "libs/glm/detail/type_mat2x4.inl"
    "libs/glm/detail/type_mat3x2.hpp"
    "libs/glm/detail/type_mat3x2.inl"
    "libs/glm/detail/type_mat3x3.hpp"
    "libs/glm/detail/type_mat3x3.inl"
    "libs/glm/detail/type_mat3x4.hpp"
    "libs/glm/detail/type_mat3x4.inl"
    "libs/glm/detail/type_mat4x2.hpp"
    "libs/glm/detail/type_mat4x2.inl"
    "libs/glm/detail/type_mat4x3.hpp"
    "libs/glm/detail/type_mat4x3.inl"
    "libs/glm/detail/type_mat4x4.hpp"
    "libs/glm/detail/type_mat4x4.inl"
    "libs/glm/detail/type_mat4x4_simd.inl"
    "libs/glm/detail/type_quat.hpp"
    "libs/glm/detail/type_quat.inl"
    "libs/glm/detail/type_quat_simd.inl"
    "libs/glm/detail/type_vec1.hpp"
    "libs/glm/detail/type_vec1.inl"
    "libs/glm/detail/type_vec2.hpp"
    "libs/glm/detail/type_vec2.inl"
    "libs/glm/detail/type_vec3.hpp"
    "libs/glm/detail/type_vec3.inl"
    "libs/glm/detail/type_vec4.hpp"
    "libs/glm/detail/type_vec4.inl"
    "libs/glm/detail/type_vec4_simd.inl"
)
source_group("libs\\glm\\detail" FILES ${libs__glm__detail})

set(libs__glm__ext
    "libs/glm/ext/matrix_clip_space.hpp"
    "libs/glm/ext/matrix_clip_space.inl"
    "libs/glm/ext/matrix_common.hpp"
    "libs/glm/ext/matrix_common.inl"
    "libs/glm/ext/matrix_double2x2.hpp"
    "libs/glm/ext/matrix_double2x2_precision.hpp"
    "libs/glm/ext/matrix_double2x3.hpp"
    "libs/glm/ext/matrix_double2x3_precision.hpp"
    "libs/glm/ext/matrix_double2x4.hpp"
    "libs/glm/ext/matrix_double2x4_precision.hpp"
    "libs/glm/ext/matrix_double3x2.hpp"
    "libs/glm/ext/matrix_double3x2_precision.hpp"
    "libs/glm/ext/matrix_double3x3.hpp"
    "libs/glm/ext/matrix_double3x3_precision.hpp"
    "libs/glm/ext/matrix_double3x4.hpp"
    "libs/glm/ext/matrix_double3x4_precision.hpp"
    "libs/glm/ext/matrix_double4x2.hpp"
    "libs/glm/ext/matrix_double4x2_precision.hpp"
    "libs/glm/ext/matrix_double4x3.hpp"
    "libs/glm/ext/matrix_double4x3_precision.hpp"
    "libs/glm/ext/matrix_double4x4.hpp"
    "libs/glm/ext/matrix_double4x4_precision.hpp"
    "libs/glm/ext/matrix_float2x2.hpp"
    "libs/glm/ext/matrix_float2x2_precision.hpp"
    "libs/glm/ext/matrix_float2x3.hpp"
    "libs/glm/ext/matrix_float2x3_precision.hpp"
    "libs/glm/ext/matrix_float2x4.hpp"
    "libs/glm/ext/matrix_float2x4_precision.hpp"
    "libs/glm/ext/matrix_float3x2.hpp"
    "libs/glm/ext/matrix_float3x2_precision.hpp"
    "libs/glm/ext/matrix_float3x3.hpp"
    "libs/glm/ext/matrix_float3x3_precision.hpp"
    "libs/glm/ext/matrix_float3x4.hpp"
    "libs/glm/ext/matrix_float3x4_precision.hpp"
    "libs/glm/ext/matrix_float4x2.hpp"
    "libs/glm/ext/matrix_float4x2_precision.hpp"
    "libs/glm/ext/matrix_float4x3.hpp"
    "libs/glm/ext/matrix_float4x3_precision.hpp"
    "libs/glm/ext/matrix_float4x4.hpp"
    "libs/glm/ext/matrix_float4x4_precision.hpp"
    "libs/glm/ext/matrix_int2x2.hpp"
    "libs/glm/ext/matrix_int2x2_sized.hpp"
    "libs/glm/ext/matrix_int2x3.hpp"
    "libs/glm/ext/matrix_int2x3_sized.hpp"
    "libs/glm/ext/matrix_int2x4.hpp"
    "libs/glm/ext/matrix_int2x4_sized.hpp"
    "libs/glm/ext/matrix_int3x2.hpp"
    "libs/glm/ext/matrix_int3x2_sized.hpp"
    "libs/glm/ext/matrix_int3x3.hpp"
    "libs/glm/ext/matrix_int3x3_sized.hpp"
    "libs/glm/ext/matrix_int3x4.hpp"
    "libs/glm/ext/matrix_int3x4_sized.hpp"
    "libs/glm/ext/matrix_int4x2.hpp"
    "libs/glm/ext/matrix_int4x2_sized.hpp"
    "libs/glm/ext/matrix_int4x3.hpp"
    "libs/glm/ext/matrix_int4x3_sized.hpp"
    "libs/glm/ext/matrix_int4x4.hpp"
    "libs/glm/ext/matrix_int4x4_sized.hpp"
    "libs/glm/ext/matrix_projection.hpp"
    "libs/glm/ext/matrix_projection.inl"
    "libs/glm/ext/matrix_relational.hpp"
    "libs/glm/ext/matrix_relational.inl"
    "libs/glm/ext/matrix_transform.hpp"
    "libs/glm/ext/matrix_transform.inl"
    "libs/glm/ext/matrix_uint2x2.hpp"
    "libs/glm/ext/matrix_uint2x2_sized.hpp"
    "libs/glm/ext/matrix_uint2x3.hpp"
    "libs/glm/ext/matrix_uint2x3_sized.hpp"
    "libs/glm/ext/matrix_uint2x4.hpp"
    "libs/glm/ext/matrix_uint2x4_sized.hpp"
    "libs/glm/ext/matrix_uint3x2.hpp"
    "libs/glm/ext/matrix_uint3x2_sized.hpp"
    "libs/glm/ext/matrix_uint3x3.hpp"
    "libs/glm/ext/matrix_uint3x3_sized.hpp"
    "libs/glm/ext/matrix_uint3x4.hpp"
    "libs/glm/ext/matrix_uint3x4_sized.hpp"
    "libs/glm/ext/matrix_uint4x2.hpp"
    "libs/glm/ext/matrix_uint4x2_sized.hpp"
    "libs/glm/ext/matrix_uint4x3.hpp"
    "libs/glm/ext/matrix_uint4x3_sized.hpp"
    "libs/glm/ext/matrix_uint4x4.hpp"
    "libs/glm/ext/matrix_uint4x4_sized.hpp"
    "libs/glm/ext/quaternion_common.hpp"
    "libs/glm/ext/quaternion_common.inl"
    "libs/glm/ext/quaternion_common_simd.inl"
    "libs/glm/ext/quaternion_double.hpp"
    "libs/glm/ext/quaternion_double_precision.hpp"
    "libs/glm/ext/quaternion_exponential.hpp"
    "libs/glm/ext/quaternion_exponential.inl"
    "libs/glm/ext/quaternion_float.hpp"
    "libs/glm/ext/quaternion_float_precision.hpp"
    "libs/glm/ext/quaternion_geometric.hpp"
    "libs/glm/ext/quaternion_geometric.inl"
    "libs/glm/ext/quaternion_relational.hpp"
    "libs/glm/ext/quaternion_relational.inl"
    "libs/glm/ext/quaternion_transform.hpp"
    "libs/glm/ext/quaternion_transform.inl"
    "libs/glm/ext/quaternion_trigonometric.hpp"
    "libs/glm/ext/quaternion_trigonometric.inl"
    "libs/glm/ext/scalar_common.hpp"
    "libs/glm/ext/scalar_common.inl"
    "libs/glm/ext/scalar_constants.hpp"
    "libs/glm/ext/scalar_constants.inl"
    "libs/glm/ext/scalar_int_sized.hpp"
    "libs/glm/ext/scalar_integer.hpp"
    "libs/glm/ext/scalar_integer.inl"
    "libs/glm/ext/scalar_packing.hpp"
    "libs/glm/ext/scalar_packing.inl"
    "libs/glm/ext/scalar_relational.hpp"
    "libs/glm/ext/scalar_relational.inl"
    "libs/glm/ext/scalar_uint_sized.hpp"
    "libs/glm/ext/scalar_ulp.hpp"
    "libs/glm/ext/scalar_ulp.inl"
    "libs/glm/ext/vector_bool1.hpp"
    "libs/glm/ext/vector_bool1_precision.hpp"
    "libs/glm/ext/vector_bool2.hpp"
    "libs/glm/ext/vector_bool2_precision.hpp"
    "libs/glm/ext/vector_bool3.hpp"
    "libs/glm/ext/vector_bool3_precision.hpp"
    "libs/glm/ext/vector_bool4.hpp"
    "libs/glm/ext/vector_bool4_precision.hpp"
    "libs/glm/ext/vector_common.hpp"
    "libs/glm/ext/vector_common.inl"
    "libs/glm/ext/vector_double1.hpp"
    "libs/glm/ext/vector_double1_precision.hpp"
    "libs/glm/ext/vector_double2.hpp"
    "libs/glm/ext/vector_double2_precision.hpp"
    "libs/glm/ext/vector_double3.hpp"
    "libs/glm/ext/vector_double3_precision.hpp"
    "libs/glm/ext/vector_double4.hpp"
    "libs/glm/ext/vector_double4_precision.hpp"
    "libs/glm/ext/vector_float1.hpp"
    "libs/glm/ext/vector_float1_precision.hpp"
    "libs/glm/ext/vector_float2.hpp"
    "libs/glm/ext/vector_float2_precision.hpp"
    "libs/glm/ext/vector_float3.hpp"
    "libs/glm/ext/vector_float3_precision.hpp"
    "libs/glm/ext/vector_float4.hpp"
    "libs/glm/ext/vector_float4_precision.hpp"
    "libs/glm/ext/vector_int1.hpp"
    "libs/glm/ext/vector_int1_sized.hpp"
    "libs/glm/ext/vector_int2.hpp"
    "libs/glm/ext/vector_int2_sized.hpp"
    "libs/glm/ext/vector_int3.hpp"
    "libs/glm/ext/vector_int3_sized.hpp"
    "libs/glm/ext/vector_int4.hpp"
    "libs/glm/ext/vector_int4_sized.hpp"
    "libs/glm/ext/vector_integer.hpp"
    "libs/glm/ext/vector_integer.inl"
    "libs/glm/ext/vector_packing.hpp"
    "libs/glm/ext/vector_packing.inl"
    "libs/glm/ext/vector_relational.hpp"
    "libs/glm/ext/vector_relational.inl"
    "libs/glm/ext/vector_uint1.hpp"
    "libs/glm/ext/vector_uint1_sized.hpp"
    "libs/glm/ext/vector_uint2.hpp"
    "libs/glm/ext/vector_uint2_sized.hpp"
    "libs/glm/ext/vector_uint3.hpp"
    "libs/glm/ext/vector_uint3_sized.hpp"
    "libs/glm/ext/vector_uint4.hpp"
    "libs/glm/ext/vector_uint4_sized.hpp"
    "libs/glm/ext/vector_ulp.hpp"
    "libs/glm/ext/vector_ulp.inl"
)
source_group("libs\\glm\\ext" FILES ${libs__glm__ext})

set(libs__glm__gtc
    "libs/glm/gtc/bitfield.hpp"
    "libs/glm/gtc/bitfield.inl"
    "libs/glm/gtc/color_space.hpp"
    "libs/glm/gtc/color_space.inl"
    "libs/glm/gtc/constants.hpp"
    "libs/glm/gtc/constants.inl"
    "libs/glm/gtc/epsilon.hpp"
    "libs/glm/gtc/epsilon.inl"
    "libs/glm/gtc/integer.hpp"
    "libs/glm/gtc/integer.inl"
    "libs/glm/gtc/matrix_access.hpp"
    "libs/glm/gtc/matrix_access.inl"
    "libs/glm/gtc/matrix_integer.hpp"
    "libs/glm/gtc/matrix_inverse.hpp"
    "libs/glm/gtc/matrix_inverse.inl"
    "libs/glm/gtc/matrix_transform.hpp"
    "libs/glm/gtc/matrix_transform.inl"
    "libs/glm/gtc/noise.hpp"
    "libs/glm/gtc/noise.inl"
    "libs/glm/gtc/packing.hpp"
    "libs/glm/gtc/packing.inl"
    "libs/glm/gtc/quaternion.hpp"
    "libs/glm/gtc/quaternion.inl"
    "libs/glm/gtc/quaternion_simd.inl"
    "libs/glm/gtc/random.hpp"
    "libs/glm/gtc/random.inl"
    "libs/glm/gtc/reciprocal.hpp"
    "libs/glm/gtc/reciprocal.inl"
    "libs/glm/gtc/round.hpp"
    "libs/glm/gtc/round.inl"
    "libs/glm/gtc/type_aligned.hpp"
    "libs/glm/gtc/type_precision.hpp"
    "libs/glm/gtc/type_precision.inl"
    "libs/glm/gtc/type_ptr.hpp"
    "libs/glm/gtc/type_ptr.inl"
    "libs/glm/gtc/ulp.hpp"
    "libs/glm/gtc/ulp.inl"
    "libs/glm/gtc/vec1.hpp"
)
source_group("libs\\glm\\gtc" FILES ${libs__glm__gtc})

set(libs__glm__gtx
    "libs/glm/gtx/associated_min_max.hpp"
    "libs/glm/gtx/associated_min_max.inl"
    "libs/glm/gtx/bit.hpp"
    "libs/glm/gtx/bit.inl"
    "libs/glm/gtx/closest_point.hpp"
    "libs/glm/gtx/closest_point.inl"
    "libs/glm/gtx/color_encoding.hpp"
    "libs/glm/gtx/color_encoding.inl"
    "libs/glm/gtx/color_space.hpp"
    "libs/glm/gtx/color_space.inl"
    "libs/glm/gtx/color_space_YCoCg.hpp"
    "libs/glm/gtx/color_space_YCoCg.inl"
    "libs/glm/gtx/common.hpp"
    "libs/glm/gtx/common.inl"
    "libs/glm/gtx/compatibility.hpp"
    "libs/glm/gtx/compatibility.inl"
    "libs/glm/gtx/component_wise.hpp"
    "libs/glm/gtx/component_wise.inl"
    "libs/glm/gtx/dual_quaternion.hpp"
    "libs/glm/gtx/dual_quaternion.inl"
    "libs/glm/gtx/easing.hpp"
    "libs/glm/gtx/easing.inl"
    "libs/glm/gtx/euler_angles.hpp"
    "libs/glm/gtx/euler_angles.inl"
    "libs/glm/gtx/extend.hpp"
    "libs/glm/gtx/extend.inl"
    "libs/glm/gtx/extended_min_max.hpp"
    "libs/glm/gtx/extended_min_max.inl"
    "libs/glm/gtx/exterior_product.hpp"
    "libs/glm/gtx/exterior_product.inl"
    "libs/glm/gtx/fast_exponential.hpp"
    "libs/glm/gtx/fast_exponential.inl"
    "libs/glm/gtx/fast_square_root.hpp"
    "libs/glm/gtx/fast_square_root.inl"
    "libs/glm/gtx/fast_trigonometry.hpp"
    "libs/glm/gtx/fast_trigonometry.inl"
    "libs/glm/gtx/float_notmalize.inl"
    "libs/glm/gtx/functions.hpp"
    "libs/glm/gtx/functions.inl"
    "libs/glm/gtx/gradient_paint.hpp"
    "libs/glm/gtx/gradient_paint.inl"
    "libs/glm/gtx/handed_coordinate_space.hpp"
    "libs/glm/gtx/handed_coordinate_space.inl"
    "libs/glm/gtx/hash.hpp"
    "libs/glm/gtx/hash.inl"
    "libs/glm/gtx/integer.hpp"
    "libs/glm/gtx/integer.inl"
    "libs/glm/gtx/intersect.hpp"
    "libs/glm/gtx/intersect.inl"
    "libs/glm/gtx/io.hpp"
    "libs/glm/gtx/io.inl"
    "libs/glm/gtx/log_base.hpp"
    "libs/glm/gtx/log_base.inl"
    "libs/glm/gtx/matrix_cross_product.hpp"
    "libs/glm/gtx/matrix_cross_product.inl"
    "libs/glm/gtx/matrix_decompose.hpp"
    "libs/glm/gtx/matrix_decompose.inl"
    "libs/glm/gtx/matrix_factorisation.hpp"
    "libs/glm/gtx/matrix_factorisation.inl"
    "libs/glm/gtx/matrix_interpolation.hpp"
    "libs/glm/gtx/matrix_interpolation.inl"
    "libs/glm/gtx/matrix_major_storage.hpp"
    "libs/glm/gtx/matrix_major_storage.inl"
    "libs/glm/gtx/matrix_operation.hpp"
    "libs/glm/gtx/matrix_operation.inl"
    "libs/glm/gtx/matrix_query.hpp"
    "libs/glm/gtx/matrix_query.inl"
    "libs/glm/gtx/matrix_transform_2d.hpp"
    "libs/glm/gtx/matrix_transform_2d.inl"
    "libs/glm/gtx/mixed_product.hpp"
    "libs/glm/gtx/mixed_product.inl"
    "libs/glm/gtx/norm.hpp"
    "libs/glm/gtx/norm.inl"
    "libs/glm/gtx/normal.hpp"
    "libs/glm/gtx/normal.inl"
    "libs/glm/gtx/normalize_dot.hpp"
    "libs/glm/gtx/normalize_dot.inl"
    "libs/glm/gtx/number_precision.hpp"
    "libs/glm/gtx/number_precision.inl"
    "libs/glm/gtx/optimum_pow.hpp"
    "libs/glm/gtx/optimum_pow.inl"
    "libs/glm/gtx/orthonormalize.hpp"
    "libs/glm/gtx/orthonormalize.inl"
    "libs/glm/gtx/perpendicular.hpp"
    "libs/glm/gtx/perpendicular.inl"
    "libs/glm/gtx/polar_coordinates.hpp"
    "libs/glm/gtx/polar_coordinates.inl"
    "libs/glm/gtx/projection.hpp"
    "libs/glm/gtx/projection.inl"
    "libs/glm/gtx/quaternion.hpp"
    "libs/glm/gtx/quaternion.inl"
    "libs/glm/gtx/range.hpp"
    "libs/glm/gtx/raw_data.hpp"
    "libs/glm/gtx/raw_data.inl"
    "libs/glm/gtx/rotate_normalized_axis.hpp"
    "libs/glm/gtx/rotate_normalized_axis.inl"
    "libs/glm/gtx/rotate_vector.hpp"
    "libs/glm/gtx/rotate_vector.inl"
    "libs/glm/gtx/scalar_multiplication.hpp"
    "libs/glm/gtx/scalar_relational.hpp"
    "libs/glm/gtx/scalar_relational.inl"
    "libs/glm/gtx/spline.hpp"
    "libs/glm/gtx/spline.inl"
    "libs/glm/gtx/std_based_type.hpp"
    "libs/glm/gtx/std_based_type.inl"
    "libs/glm/gtx/string_cast.hpp"
    "libs/glm/gtx/string_cast.inl"
    "libs/glm/gtx/texture.hpp"
    "libs/glm/gtx/texture.inl"
    "libs/glm/gtx/transform.hpp"
    "libs/glm/gtx/transform.inl"
    "libs/glm/gtx/transform2.hpp"
    "libs/glm/gtx/transform2.inl"
    "libs/glm/gtx/type_aligned.hpp"
    "libs/glm/gtx/type_aligned.inl"
    "libs/glm/gtx/type_trait.hpp"
    "libs/glm/gtx/type_trait.inl"
    "libs/glm/gtx/vec_swizzle.hpp"
    "libs/glm/gtx/vector_angle.hpp"
    "libs/glm/gtx/vector_angle.inl"
    "libs/glm/gtx/vector_query.hpp"
    "libs/glm/gtx/vector_query.inl"
    "libs/glm/gtx/wrap.hpp"
    "libs/glm/gtx/wrap.inl"
)
source_group("libs\\glm\\gtx" FILES ${libs__glm__gtx})

set(libs__stb_image
    "libs/stb_image/stb_image.h"
)
source_group("libs\\stb_image" FILES ${libs__stb_image})

set(src
    "src/core.h"
    "src/gepch.cpp"
    "src/gepch.h"
    "src/Object.h"
)
source_group("src" FILES ${src})

set(src__App
    "src/App/Action.cpp"
    "src/App/Action.h"
    "src/App/CameraEventHandler.cpp"
    "src/App/CameraEventHandler.h"
    "src/App/CharacterObject.cpp"
    "src/App/CharacterObject.h"
    "src/App/Controller.cpp"
    "src/App/Controller.h"
    "src/App/EventHandlers.h"
    "src/App/Game.cpp"
    "src/App/Game.h"
    "src/App/GameObject.cpp"
    "src/App/GameObject.h"
    "src/App/Input.cpp"
    "src/App/InputHandler.h"
    "src/App/Interfaces.h"
    "src/App/main.cpp"
    "src/App/Random.cpp"
    "src/App/Random.h"
    "src/App/Sprite.cpp"
    "src/App/Sprite.h"
    "src/App/Tests/TestGame.cpp"
    "src/App/Tests/TestGame.h"
    "src/App/TextureMap.cpp"
    "src/App/TextureMap.h"
    "src/App/Vector2D.cpp"
    "src/App/Vector2D.h"
    "src/App/WorldGeneration/Noise.cpp"
    "src/App/WorldGeneration/Noise.h"
    "src/App/WorldGeneration/Tile.cpp"
    "src/App/WorldGeneration/Tile.h"
    "src/App/WorldGeneration/World.cpp"
    "src/App/WorldGeneration/World.h"
)
source_group("src\\App" FILES ${src__App})

set(src__App__Tests
    "src/App/Tests/Tests.cpp"
    "src/App/Tests/Tests.h"
)
source_group("src\\App\\Tests" FILES ${src__App__Tests})

set(src__GE
    "src/GE/BaseApp.cpp"
    "src/GE/BaseApp.h"
    "src/GE/Camera.cpp"
    "src/GE/Camera.h"
    "src/GE/Clock.cpp"
    "src/GE/Clock.h"
    "src/GE/Logger.cpp"
    "src/GE/Logger.h"
    "src/GE/MousePosition.h"
    "src/GE/Window.cpp"
    "src/GE/Window.h"
)
source_group("src\\GE" FILES ${src__GE})

set(src__GE__Events
    "src/GE/Events/Event.cpp"
    "src/GE/Events/Event.h"
    "src/GE/Events/EventHandler.cpp"
    "src/GE/Events/EventHandler.h"
)
source_group("src\\GE\\Events" FILES ${src__GE__Events})

set(src__GE__Events__Keys
    "src/GE/Events/Keys/KeyEvent.cpp"
    "src/GE/Events/Keys/KeyEvent.h"
    "src/GE/Events/Keys/KeyHeldEvent.cpp"
    "src/GE/Events/Keys/KeyHeldEvent.h"
    "src/GE/Events/Keys/KeyPressedEvent.cpp"
    "src/GE/Events/Keys/KeyPressedEvent.h"
    "src/GE/Events/Keys/KeyReleasedEvent.cpp"
    "src/GE/Events/Keys/KeyReleasedEvent.h"
)
source_group("src\\GE\\Events\\Keys" FILES ${src__GE__Events__Keys})

set(src__GE__Events__Mouse
    "src/GE/Events/Mouse/MouseClickedEvent.cpp"
    "src/GE/Events/Mouse/MouseClickedEvent.h"
    "src/GE/Events/Mouse/MouseEvent.h"
    "src/GE/Events/Mouse/MouseMoveEvent.cpp"
    "src/GE/Events/Mouse/MouseMoveEvent.h"
    "src/GE/Events/Mouse/MouseReleasedEvent.cpp"
    "src/GE/Events/Mouse/MouseReleasedEvent.h"
    "src/GE/Events/Mouse/MouseScrolledEvent.cpp"
    "src/GE/Events/Mouse/MouseScrolledEvent.h"
)
source_group("src\\GE\\Events\\Mouse" FILES ${src__GE__Events__Mouse})

set(src__GE__Events__Window
    "src/GE/Events/Window/WindowClosedEvent.cpp"
    "src/GE/Events/Window/WindowClosedEvent.h"
    "src/GE/Events/Window/WindowResizedEvent.cpp"
    "src/GE/Events/Window/WindowResizedEvent.h"
)
source_group("src\\GE\\Events\\Window" FILES ${src__GE__Events__Window})

set(src__GE__Graphics
    "src/GE/Graphics/FontLoader.cpp"
    "src/GE/Graphics/FontLoader.h"
    "src/GE/Graphics/FontRenderer.cpp"
    "src/GE/Graphics/FontRenderer.h"
    "src/GE/Graphics/Renderer.cpp"
    "src/GE/Graphics/Renderer.h"
    "src/GE/Graphics/Shader.cpp"
    "src/GE/Graphics/Shader.h"
    "src/GE/Graphics/Texture.cpp"
    "src/GE/Graphics/Texture.h"
    "src/GE/Graphics/TextureCache.cpp"
    "src/GE/Graphics/TextureCache.h"
)
source_group("src\\GE\\Graphics" FILES ${src__GE__Graphics})

set(ALL_FILES
    ${no_group_source_files}
    ${libs__glm}
    ${libs__glm__detail}
    ${libs__glm__ext}
    ${libs__glm__gtc}
    ${libs__glm__gtx}
    ${libs__stb_image}
    ${src}
    ${src__App}
    ${src__App__Tests}
    ${src__GE}
    ${src__GE__Events}
    ${src__GE__Events__Keys}
    ${src__GE__Events__Mouse}
    ${src__GE__Events__Window}
    ${src__GE__Graphics}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

add_precompiled_header(${PROJECT_NAME} "gepch.h" "src/gepch.cpp")

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE GameEngine)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_DEBUG   "GameEngine"
    TARGET_NAME_DIST    "GameEngine"
    TARGET_NAME_RELEASE "GameEngine"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DEBUG   "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Debug-windows-x86/GameEngine/"
    OUTPUT_DIRECTORY_DIST    "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Dist-windows-x86/GameEngine/"
    OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Release-windows-x86/GameEngine/"
)
################################################################################
# MSVC runtime library
################################################################################
get_property(MSVC_RUNTIME_LIBRARY_DEFAULT TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY)
string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
    $<$<CONFIG:Debug>:
        MultiThreadedDebug
    >
    $<$<CONFIG:Dist>:
        MultiThreaded
    >
    $<$<CONFIG:Release>:
        MultiThreaded
    >
    $<$<NOT:$<OR:$<CONFIG:Debug>,$<CONFIG:Dist>,$<CONFIG:Release>>>:${MSVC_RUNTIME_LIBRARY_DEFAULT}>
)
set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})

################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src;"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs;"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/spdlog/include;"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/GLFW/include;"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/Glad/include;"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/stb_image;"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/glm;"
    "${CMAKE_CURRENT_SOURCE_DIR}/..;"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/freetype;"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/freetype/include"
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:Debug>:"
        "GE_DEBUG"
    ">"
    "$<$<CONFIG:Dist>:"
        "GE_DIST"
    ">"
    "$<$<CONFIG:Release>:"
        "GE_RELEASE"
    ">"
    "GE_BUILD;"
    "UNICODE;"
    "_UNICODE"
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /Od;
            /ZI
        >
        $<$<CONFIG:Dist>:
            /Gm-;
            /Ox;
            /Oi;
            /GF;
            /Gy;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
        >
        $<$<CONFIG:Release>:
            /Gm-;
            /Ox;
            /Oi;
            /GF;
            /Gy;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
        >
        /std:c++17;
        /W3;
        ${DEFAULT_CXX_EXCEPTION_HANDLING}
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /DEBUG;
            /INCREMENTAL
        >
        $<$<CONFIG:Dist>:
            /DEBUG:FULL;
            /OPT:REF;
            /OPT:ICF;
            /INCREMENTAL:NO
        >
        $<$<CONFIG:Release>:
            /DEBUG:FULL;
            /OPT:REF;
            /OPT:ICF;
            /INCREMENTAL:NO
        >
        /SUBSYSTEM:CONSOLE;
        /FORCE:MULTIPLE
    )
endif()

################################################################################
# Post build events
################################################################################
add_custom_command_if(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMANDS
    COMMAND   $<CONFIG:Debug> xcopy "$<SHELL_PATH:${CMAKE_CURRENT_SOURCE_DIR}/>/res" "${OUTPUT_DIRECTORY}/res" /e /y /i /r /d
    COMMAND $<CONFIG:Release> xcopy "$<SHELL_PATH:${CMAKE_CURRENT_SOURCE_DIR}/>/res" "${OUTPUT_DIRECTORY}/res" /e /y /i /r /d
)

################################################################################
# Dependencies
################################################################################
add_dependencies(${PROJECT_NAME}
    GLFW
    ImGui
    Glad
    freetype
)

# Link with other targets.
target_link_libraries(${PROJECT_NAME} PRIVATE
    GLFW
    ImGui
    Glad
    freetype
)

set(ADDITIONAL_LIBRARY_DEPENDENCIES
    "opengl32;"
    "winmm"
)
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

