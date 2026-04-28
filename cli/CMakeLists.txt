cmake_minimum_required(VERSION 3.16)
project(libigl_cli VERSION 2.5.0)

# Update CMake module path to find recipes and helper functions
set(IGL_CMAKE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../cmake)
list(PREPEND CMAKE_MODULE_PATH
    ${IGL_CMAKE_DIR}
    ${IGL_CMAKE_DIR}/igl
    ${IGL_CMAKE_DIR}/find
    ${IGL_CMAKE_DIR}/recipes/external
)
set_property(GLOBAL PROPERTY __igl_module_path ${CMAKE_MODULE_PATH})

# Include CMake helper functions
include(igl_add_library)
include(igl_add_test)
include(igl_add_tutorial)
include(igl_copy_dll)
include(igl_include)
include(igl_install)
include(igl_target_sources)

# Include libigl module targets
set(libigl_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)
include(libigl)

# Choose which chapters to compile
option(LIBIGL_CLI_CHAPTER1 "Compile libigl CLI applications chapter 1" ON)
option(LIBIGL_CLI_CHAPTER2 "Compile libigl CLI applications chapter 2" ON)
option(LIBIGL_CLI_CHAPTER3 "Compile libigl CLI applications chapter 3" ON)
option(LIBIGL_CLI_CHAPTER4 "Compile libigl CLI applications chapter 4" ON)
option(LIBIGL_CLI_CHAPTER5 "Compile libigl CLI applications chapter 5" ON)
option(LIBIGL_CLI_CHAPTER6 "Compile libigl CLI applications chapter 6" ON)
option(LIBIGL_CLI_CHAPTER7 "Compile libigl CLI applications chapter 7" ON)
option(LIBIGL_CLI_CHAPTER8 "Compile libigl CLI applications chapter 8" ON)
option(LIBIGL_CLI_CHAPTER9 "Compile libigl CLI applications chapter 9" ON)
option(LIBIGL_CLI_CHAPTER10 "Compile libigl CLI applications chapter 10" ON)

# Download tutorial data
include(libigl_tutorial_data)

if(NOT TARGET igl::glfw)
    message(WARNING "Most CLI applications depend on OpenGL and glfw. Use `cmake -DLIBIGL_GLFW=ON ..`")
endif()

# Custom function for adding CLI applications
function(igl_add_cli name)
    # Only create CLI app if dependencies have been enabled in the current build
    foreach(module IN ITEMS ${ARGN})
        if(NOT TARGET ${module})
            return()
        endif()
    endforeach()

    message(STATUS "Creating libigl CLI app: ${name}")
    # get all cpp files in ${CMAKE_CURRENT_SOURCE_DIR}/${name}/
    file(GLOB SRCFILES ${CMAKE_CURRENT_SOURCE_DIR}/${name}/*.cpp)
    add_executable(${name} ${SRCFILES})
    
    # Include libigl/include and the current folder for local headers
    target_include_directories(${name} PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
        ${CMAKE_CURRENT_SOURCE_DIR}/${name}
    )
    if(APPLE)
        target_include_directories(${name} PRIVATE /opt/homebrew/include)
    endif()
    
    target_link_libraries(${name} PRIVATE
        igl::core
        igl::tutorial_data
        ${ARGN}
    )

    set_target_properties(${name} PROPERTIES FOLDER Libigl_CLI)

    # Do this codesign only on macOS
    if(APPLE)
      add_custom_command(TARGET ${name} POST_BUILD
        COMMAND codesign -f -s - $<TARGET_FILE:${name}>
        COMMENT "Codesigning ${name}"
      )
    endif()
endfunction()

# Chapter 1
if(LIBIGL_CLI_CHAPTER1)
    igl_add_cli(101_FileIO)
    igl_add_cli(102_DrawMesh igl::glfw)
    igl_add_cli(103_Events igl::glfw)
    igl_add_cli(104_Colors igl::glfw)
    igl_add_cli(105_Overlays igl::imgui)
    igl_add_cli(106_ViewerMenu igl::imgui)
    igl_add_cli(107_MultipleMeshes igl::glfw)
    igl_add_cli(108_MultipleViews igl::glfw)
    igl_add_cli(109_ImGuizmo igl::imgui)
    igl_add_cli(110_MshView igl::glfw)
    igl_add_cli(111_MatCap igl::glfw igl::stb)
    igl_add_cli(112_Selection igl::imgui)
    igl_add_cli(113_Shadows igl::imgui igl::stb)
    igl_add_cli(114_CustomShader igl::glfw)
endif()

# Chapter 2
if(LIBIGL_CLI_CHAPTER2)
    igl_add_cli(201_Normals igl::glfw)
    igl_add_cli(202_GaussianCurvature igl::glfw)
    igl_add_cli(203_CurvatureDirections igl::glfw)
    igl_add_cli(204_Gradient igl::glfw)
    igl_add_cli(205_Laplacian igl::glfw)
    igl_add_cli(206_GeodesicDistance igl::glfw)
    igl_add_cli(207_PolygonLaplacian igl::glfw)
endif()

# Chapter 3
if(LIBIGL_CLI_CHAPTER3)
    igl_add_cli(301_Slice igl::glfw)
    igl_add_cli(302_Sort igl::glfw)
    igl_add_cli(303_LaplaceEquation igl::glfw)
    igl_add_cli(304_LinearEqualityConstraints igl::glfw)
    igl_add_cli(305_QuadraticProgramming igl::glfw)
    igl_add_cli(306_EigenDecomposition igl::glfw)
endif()

# Chapter 4
if(LIBIGL_CLI_CHAPTER4)
    igl_add_cli(401_BiharmonicDeformation igl::glfw)
    igl_add_cli(402_PolyharmonicDeformation igl::glfw)
    igl_add_cli(403_BoundedBiharmonicWeights igl::glfw)
    igl_add_cli(404_DualQuaternionSkinning igl::glfw)
    igl_add_cli(405_AsRigidAsPossible igl::glfw)
    igl_add_cli(406_FastAutomaticSkinningTransformations igl::glfw)
    igl_add_cli(407_BiharmonicCoordinates igl::glfw)
    igl_add_cli(408_DirectDeltaMush igl::glfw)
    igl_add_cli(409_Kelvinlets igl::imgui)
endif()

# Chapter 5
if(LIBIGL_CLI_CHAPTER5)
    igl_add_cli(501_HarmonicParam igl::glfw)
    igl_add_cli(502_LSCMParam igl::glfw)
    igl_add_cli(503_ARAPParam igl::glfw)
    igl_add_cli(504_Planarization igl::glfw)
endif()

# Chapter 6
if(LIBIGL_CLI_CHAPTER6)
    igl_add_cli(601_Serialization igl::glfw igl::xml)
    igl_add_cli(602_Matlab igl::glfw igl_restricted::matlab)
    igl_add_cli(604_Triangle igl::glfw igl_restricted::triangle)
    igl_add_cli(605_Tetgen igl::glfw igl_copyleft::tetgen)
    igl_add_cli(606_AmbientOcclusion igl::glfw igl::embree)
    igl_add_cli(607_ScreenCapture igl::glfw igl::stb)
    igl_add_cli(608_RayTrace igl::stb igl::embree)
    igl_add_cli(609_Boolean igl::glfw igl_copyleft::cgal)
    igl_copy_dll(609_Boolean)
    igl_add_cli(610_CSGTree igl::glfw igl_copyleft::cgal)
    igl_copy_dll(610_CSGTree)
endif()

# Chapter 7
if(LIBIGL_CLI_CHAPTER7)
    igl_add_cli(701_Statistics igl::glfw)
    igl_add_cli(702_WindingNumber igl::glfw)
    igl_add_cli(703_Decimation igl::glfw)
    igl_add_cli(704_SignedDistance igl::glfw)
    igl_add_cli(705_MarchingCubes igl::glfw)
    igl_add_cli(706_FacetOrientation igl::glfw igl::embree)
    igl_add_cli(707_SweptVolume igl::glfw)
    igl_add_cli(708_Picking igl::glfw)
    igl_add_cli(709_SLIM igl::glfw)
    igl_add_cli(710_SCAF igl::glfw igl_restricted::triangle)
endif()

# Chapter 8
if(LIBIGL_CLI_CHAPTER8)
    igl_add_cli(801_Subdivision igl::glfw)
    igl_add_cli(802_DataSmoothing igl::glfw)
    igl_add_cli(803_ShapeUp igl::glfw)
    igl_add_cli(804_MarchingTets igl::glfw igl_copyleft::tetgen)
    igl_add_cli(805_MeshImplicitFunction igl::glfw igl_copyleft::core)
    igl_add_cli(806_HeatGeodesics igl::glfw)
    igl_add_cli(806_HeatGeodesics_CLI)
    igl_add_cli(807_FastWindingNumber igl::glfw igl_copyleft::cgal)
    igl_copy_dll(807_FastWindingNumber)
    igl_add_cli(808_IterativeClosestPoint igl::glfw)
    igl_add_cli(809_ExplodedView igl::glfw)
    igl_add_cli(810_BlueNoise igl::glfw)
endif()

# Chapter 9
if(LIBIGL_CLI_CHAPTER9)
    igl_add_cli(901_VectorFieldSmoothing igl::glfw)
    igl_add_cli(902_VectorParallelTransport igl::glfw)
    igl_add_cli(903_FastFindSelfIntersections igl::glfw igl::predicates )
    igl_add_cli(904_FastFindIntersections igl::glfw igl::predicates)
    igl_add_cli(905_Isolines igl::imgui igl::glfw)
    igl_add_cli(906_TrimWithSolid igl::glfw igl_copyleft::cgal)
    igl_add_cli(907_DynamicAABB igl::glfw)
    igl_add_cli(908_IntersectionBlockingDecimation igl::glfw igl::predicates)
    igl_add_cli(909_BatchMarchingCubes igl::glfw)
    igl_add_cli(910_OrientedBoundingBox igl::glfw igl_copyleft::cgal)
endif()

# Chapter 10
if(LIBIGL_CLI_CHAPTER10)
  igl_add_cli(1001_LipschitzOctree igl::glfw)
  igl_add_cli(1002_EytzingerAABB igl::glfw)
  igl_add_cli(1003_WindingNumber2D igl::glfw)
  igl_add_cli(1004_SplineDistance igl::glfw igl::cycodebase igl::predicates)
  igl_add_cli(1005_GeodesicVoronoiDiagram igl::glfw)
  igl_add_cli(1006_RandomRotate)
endif()
