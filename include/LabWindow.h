//
// Created by m1504 on 24-5-9.
//

#ifndef LABWINDOW_H
#define LABWINDOW_H
#include <string>

class CLabWindow {
public:
    virtual ~CLabWindow();
    virtual void Init();
    virtual void Begin();
    virtual void OnPaint();
    virtual void Exit();

    virtual void ProcessInput();

    virtual void LoadGLFW();
    virtual void LoadGLAD();

    std::string title = "LabWindow";
    int width = 800;
    int height = 600;

    struct GLFWwindow *window;
protected:
    static bool bGLFWInitialized;
};

#endif //LABWINDOW_H
