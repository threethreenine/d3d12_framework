#ifndef GAMEMAIN_H
#define GAMEMAIN_H

#include <vector>
#include "Game.h"
#include "Camera.h"
#include "TestGraphicsPipeline.h"
#include "TestModel.h"

class GameMain : public Game
{
  public:
    GameMain(WCHAR* title);
    ~GameMain();
    
  protected:
    /// <summary>
    /// Loads the content for the game
    /// </summary>
    void LoadContent();
    
    /// <summary>
    /// Unloads the content for the game before the dealloction of the instance
    /// </summary>
    void UnloadContent();
    
    /// <summary>
    /// Updates the game state
    /// </summary>
    /// <param name="step_ms">
    /// number of milliseconds since the last frame based on the configured frame rate
    /// </param>
    /// <param name="actual_ms">
    /// actual number of milliseconds since the last frame
    /// </param>
    void Update(UINT step_ms, UINT actual_ms);
    
    /// <summary>
    /// Draws the current frame
    /// </summary>
    /// <param name="step_ms">
    /// number of milliseconds since the last frame based on the configured frame rate
    /// </param>
    /// <param name="actual_ms">
    /// actual number of milliseconds since the last frame
    /// </param>
    void Draw(UINT step_ms, UINT actual_ms);
    
    /// <summary>
    /// Handler for when the window is resized
    /// </summary>
    /// <param name="width">
    /// width of the new client area, in pixels 
    /// </param>
    /// <param name="height">
    /// height of the new client area, in pixels
    /// </param>
    void OnResize(UINT width,UINT height);
    
  private:
    // disabled
    GameMain(const GameMain& cpy);
    GameMain& operator=(const GameMain& cpy);

    /// <summary>
    /// Updates m_camera based on m_camera_angle
    /// </summary>
    void UpdateCamera();

    /// <summary>
    /// camera for the test viewport
    /// </summary>
    Camera* m_camera;

    /// <summary>
    /// angle (in radians) of the camera orbiting the world space's origin
    /// </summary>
    float m_camera_angle;

    /// <summary>
    /// graphics pipeline for the test case
    /// </summary>
    TestGraphicsPipeline* m_pipeline;

    /// <summary>
    /// model for the test case
    /// </summary>
    TestModel* m_model;
};

#endif /* GAMEMAIN_H */
