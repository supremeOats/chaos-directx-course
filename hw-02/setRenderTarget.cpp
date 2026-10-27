#include "CDXRenderer.h"
#include <iostream>

int main()
{
    D3DRendererContext ctx;

    CDXRenderer renderer(ctx);
    renderer.prepareForRendering();

    std::cout << "Render prepared\n";

    const float RED[4] = {1.0, 0.0, 0.0, 1.0};
    renderer.clearTarget(RED);

    std::cout << "Target cleared\n";

    return 0;
}
