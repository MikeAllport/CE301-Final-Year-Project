//#include "imgui_impl_opengl3.h"
//
//// Functions
//bool    ImGui_ImplOpenGL3_Init(const char* glsl_version)
//{
//    // Query for GL version (e.g. 320 for GL 3.2)
//#if !defined(IMGUI_IMPL_OPENGL_ES2)
//    GLint major, minor;
//    glGetIntegerv(GL_MAJOR_VERSION, &major);
//    glGetIntegerv(GL_MINOR_VERSION, &minor);
//    g_GlVersion = (GLuint)(major * 100 + minor * 10);
//#else
//    g_GlVersion = 200; // GLES 2
//#endif
//
//    // Setup back-end capabilities flags
//    ImGuiIO& io = ImGui::GetIO();
//    io.BackendRendererName = "imgui_impl_opengl3";
//#if IMGUI_IMPL_OPENGL_MAY_HAVE_VTX_OFFSET
//    if (g_GlVersion >= 320)
//        io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;  // We can honor the ImDrawCmd::VtxOffset field, allowing for large meshes.
//#endif
//
//    // Store GLSL version string so we can refer to it later in case we recreate shaders.
//    // Note: GLSL version is NOT the same as GL version. Leave this to NULL if unsure.
//#if defined(IMGUI_IMPL_OPENGL_ES2)
//    if (glsl_version == NULL)
//        glsl_version = "#version 100";
//#elif defined(IMGUI_IMPL_OPENGL_ES3)
//    if (glsl_version == NULL)
//        glsl_version = "#version 300 es";
//#elif defined(__APPLE__)
//    if (glsl_version == NULL)
//        glsl_version = "#version 150";
//#else
//    if (glsl_version == NULL)
//        glsl_version = "#version 130";
//#endif
//    IM_ASSERT((int)strlen(glsl_version) + 2 < IM_ARRAYSIZE(g_GlslVersionString));
//    strcpy(g_GlslVersionString, glsl_version);
//    strcat(g_GlslVersionString, "\n");
//
//    // Debugging construct to make it easily visible in the IDE and debugger which GL loader has been selected.
//    // The code actually never uses the 'gl_loader' variable! It is only here so you can read it!
//    // If auto-detection fails or doesn't select the same GL loader file as used by your application,
//    // you are likely to get a crash below.
//    // You can explicitly select a loader by using '#define IMGUI_IMPL_OPENGL_LOADER_XXX' in imconfig.h or compiler command-line.
//    const char* gl_loader = "Unknown";
//    IM_UNUSED(gl_loader);
//#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
//    gl_loader = "GL3W";
//#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
//    gl_loader = "GLEW";
//#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
//    gl_loader = "GLAD";
//#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD2)
//    gl_loader = "GLAD2";
//#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING2)
//    gl_loader = "glbinding2";
//#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING3)
//    gl_loader = "glbinding3";
//#elif defined(IMGUI_IMPL_OPENGL_LOADER_CUSTOM)
//    gl_loader = "custom";
//#else
//    gl_loader = "none";
//#endif
//
//    // Make an arbitrary GL call (we don't actually need the result)
//    // IF YOU GET A CRASH HERE: it probably means that you haven't initialized the OpenGL function loader used by this code.
//    // Desktop OpenGL 3/4 need a function loader. See the IMGUI_IMPL_OPENGL_LOADER_xxx explanation above.
//    GLint current_texture;
//    glGetIntegerv(GL_TEXTURE_BINDING_2D, &current_texture);
//
//    return true;
//}
//
//static void ImGui_ImplOpenGL3_SetupRenderState(ImDrawData* draw_data, int fb_width, int fb_height, GLuint vertex_array_object)
//{
//    // Setup render state: alpha-blending enabled, no face culling, no depth testing, scissor enabled, polygon fill
//    glEnable(GL_BLEND);
//    glBlendEquation(GL_FUNC_ADD);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glDisable(GL_CULL_FACE);
//    glDisable(GL_DEPTH_TEST);
//    glEnable(GL_SCISSOR_TEST);
//#ifdef GL_POLYGON_MODE
//    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//#endif
//
//    // Support for GL 4.5 rarely used glClipControl(GL_UPPER_LEFT)
//    bool clip_origin_lower_left = true;
//#if defined(GL_CLIP_ORIGIN) && !defined(__APPLE__)
//    GLenum current_clip_origin = 0; glGetIntegerv(GL_CLIP_ORIGIN, (GLint*)&current_clip_origin);
//    if (current_clip_origin == GL_UPPER_LEFT)
//        clip_origin_lower_left = false;
//#endif
//
//    // Setup viewport, orthographic projection matrix
//    // Our visible imgui space lies from draw_data->DisplayPos (top left) to draw_data->DisplayPos+data_data->DisplaySize (bottom right). DisplayPos is (0,0) for single viewport apps.
//    glViewport(0, 0, (GLsizei)fb_width, (GLsizei)fb_height);
//    float L = draw_data->DisplayPos.x;
//    float R = draw_data->DisplayPos.x + draw_data->DisplaySize.x;
//    float T = draw_data->DisplayPos.y;
//    float B = draw_data->DisplayPos.y + draw_data->DisplaySize.y;
//    if (!clip_origin_lower_left) { float tmp = T; T = B; B = tmp; } // Swap top and bottom if origin is upper left
//    const float ortho_projection[4][4] =
//    {
//        { 2.0f / (R - L),   0.0f,         0.0f,   0.0f },
//        { 0.0f,         2.0f / (T - B),   0.0f,   0.0f },
//        { 0.0f,         0.0f,        -1.0f,   0.0f },
//        { (R + L) / (L - R),  (T + B) / (B - T),  0.0f,   1.0f },
//    };
//    glUseProgram(g_ShaderHandle);
//    glUniform1i(g_AttribLocationTex, 0);
//    glUniformMatrix4fv(g_AttribLocationProjMtx, 1, GL_FALSE, &ortho_projection[0][0]);
//#ifdef GL_SAMPLER_BINDING
//    glBindSampler(0, 0); // We use combined texture/sampler state. Applications using GL 3.3 may set that otherwise.
//#endif
//
//    (void)vertex_array_object;
//#ifndef IMGUI_IMPL_OPENGL_ES2
//    glBindVertexArray(vertex_array_object);
//#endif
//
//    // Bind vertex/index buffers and setup attributes for ImDrawVert
//    glBindBuffer(GL_ARRAY_BUFFER, g_VboHandle);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_ElementsHandle);
//    glEnableVertexAttribArray(g_AttribLocationVtxPos);
//    glEnableVertexAttribArray(g_AttribLocationVtxUV);
//    glEnableVertexAttribArray(g_AttribLocationVtxColor);
//    glVertexAttribPointer(g_AttribLocationVtxPos, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid*)IM_OFFSETOF(ImDrawVert, pos));
//    glVertexAttribPointer(g_AttribLocationVtxUV, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid*)IM_OFFSETOF(ImDrawVert, uv));
//    glVertexAttribPointer(g_AttribLocationVtxColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(ImDrawVert), (GLvoid*)IM_OFFSETOF(ImDrawVert, col));
//}
