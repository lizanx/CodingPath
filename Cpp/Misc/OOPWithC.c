#include <stdio.h>
#include <stdlib.h>

// Shape interface
struct Shape;

typedef struct ShapeOps
{
    double (*area)(const struct Shape *self);
    void (*draw)(const struct Shape *self);
    void (*destroy)(struct Shape *self);
} ShapeOps;

// Base class(interface)
typedef struct Shape
{
    const ShapeOps *ops; // vtable_ptr, position it as first field
    double center_x;     // common data
    double center_y;     // common data
} Shape;

// Rectangle
typedef struct Rectangle
{
    Shape base;    // Must be the first field
    double width;  // Rectangle-specific data
    double height; // Rectangle-specific data
} Rectangle;

double rectangle_area(const Shape *shape)
{
    const Rectangle *rectangle = (const Rectangle *)shape;
    return rectangle->width * rectangle->height;
}

void rectangle_draw(const Shape *shape)
{
    const Rectangle *rectangle = (const Rectangle *)shape;
    printf("Drawing Rectangle(center at %lf,%lf w=%lf h=%lf)\n",
           rectangle->base.center_x, rectangle->base.center_y,
           rectangle->width, rectangle->height);
}

void rectangle_destroy(Shape *shape)
{
    const Rectangle *rectangle = (const Rectangle *)shape;
    printf("Destroying Rectangle(center at %lf,%lf w=%lf h=%lf)\n",
           rectangle->base.center_x, rectangle->base.center_y,
           rectangle->width, rectangle->height);
    free(shape);
}

static const ShapeOps rectangle_ops =
    {
        .area = rectangle_area,
        .draw = rectangle_draw,
        .destroy = rectangle_destroy};

Rectangle *rectangle_new(double center_x, double center_y, double width, double height)
{
    if (width <= 0 || height <= 0)
    {
        printf("Width and height of Rectangle must be positive.\n");
        return NULL;
    }

    Rectangle *rectangle = malloc(sizeof(Rectangle));
    if (!rectangle)
    {
        printf("Failed to allocate memory for Rectangle!\n");
        return NULL;
    }
    rectangle->base.ops = &rectangle_ops;
    rectangle->base.center_x = center_x;
    rectangle->base.center_y = center_y;
    rectangle->width = width;
    rectangle->height = height;

    return rectangle;
}

// Circle
typedef struct Circle
{
    Shape base;    // Must be the first field
    double radius; // Circle-specific data
} Circle;

double circle_area(const Shape *shape)
{
    const Circle *circle = (const Circle *)shape;
    return 3.1416 * circle->radius * circle->radius;
}

void circle_draw(const Shape *shape)
{
    const Circle *circle = (const Circle *)shape;
    printf("Drawing Circle(center at %lf,%lf r=%lf)\n",
           circle->base.center_x, circle->base.center_y,
           circle->radius);
}

void circle_destroy(Shape *shape)
{
    const Circle *circle = (const Circle *)shape;
    printf("Destroying Circle(center at %lf,%lf r=%lf)\n",
           circle->base.center_x, circle->base.center_y,
           circle->radius);
    free(shape);
}

static const ShapeOps circle_ops =
    {
        .area = circle_area,
        .draw = circle_draw,
        .destroy = circle_destroy};

Circle *circle_new(double center_x, double center_y, double radius)
{
    if (radius <= 0)
    {
        printf("Radius of Circle must be positive.\n");
        return NULL;
    }

    Circle *circle = malloc(sizeof(Circle));
    if (!circle)
    {
        printf("Failed to allocate memory for Circle!\n");
        return NULL;
    }
    circle->base.ops = &circle_ops;
    circle->base.center_x = center_x;
    circle->base.center_y = center_y;
    circle->radius = radius;

    return circle;
}

#define SHAPES_COUNT 4
int main(int argc, char *argv[])
{
    Shape *shapes[SHAPES_COUNT] = {
        (Shape *)rectangle_new(1, 2, 3, 4),
        (Shape *)rectangle_new(5, 6, 7, 8),
        (Shape *)circle_new(11, 22, 3),
        (Shape *)circle_new(44, 55, 6),
    };

    for (size_t i = 0; i < SHAPES_COUNT; ++i)
    {
        printf("----------------- Shape[%zu] -----------------\n", i);
        if (shapes[i])
        {
            shapes[i]->ops->draw(shapes[i]);
            printf("Area: %lf\n", shapes[i]->ops->area(shapes[i]));
        }
        else
        {
            printf("ERROR: Invalid shape pointer!\n");
        }
    }

    printf("\n### Releasing shapes... ###\n");
    for (size_t i = 0; i < SHAPES_COUNT; ++i)
    {
        if (shapes[i])
            shapes[i]->ops->destroy(shapes[i]);
    }

    return EXIT_SUCCESS;
}
