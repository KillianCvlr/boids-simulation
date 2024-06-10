#pragma once

#include <SDL.h>
#include <iostream>
#include <memory>
#include <cmath>

#include "SDLColors.hpp"

class God;


class RenderHandler {
public:
    RenderHandler(char const *title, int const width, int const height);
    ~RenderHandler();

    void renderUniverse(const God* god);
    void renderCells(const God* god);
    void renderFieldViews(const God* god);
    void renderFieldView(int x, int y, float angle);
    void renderQuadTree(const God* god);
    void renderVelocity(const God* god);

    void renderProximity(const God* god);
    void renderNeighboringLinks(const God* god);

    void drawrect(int x, int y, int x2, int y2);
    void drawCircle(int x, int y, int radius);
    void drawDisk(int x, int y, int radius);

    inline std::pair<int, int> getSize() const { return size_; }

    inline void switchRenderQuadTree() { renderQuadTree_ = !renderQuadTree_; }
    inline void switchRenderFieldViews() { renderFieldViews_ = !renderFieldViews_; }
    inline void switchRenderCells() { renderCells_ = !renderCells_; }
    inline void switchRenderProximity() { renderProximity_ = !renderProximity_; }
    inline void switchRenderNeighboringLinks() { renderNeighboringLinks_ = !renderNeighboringLinks_; }
    inline void switchRenderVelocity() { renderVelocity_ = !renderVelocity_; }

private:
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window_;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer_;
    std::pair<int, int> size_;

    bool renderQuadTree_ = false;
    bool renderFieldViews_ = false;
    bool renderCells_ = true;
    bool renderProximity_ = false;
    bool renderNeighboringLinks_ = false;
    bool renderVelocity_ = true;

};

double mapValue(double value, double fromLow, double fromHigh, double toLow, double toHigh);