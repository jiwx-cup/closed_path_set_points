#include <bits/stdc++.h>

using namespace std;

struct Point
{
    int x, y;
};

// global point needed for sorting points with reference
// to the first point. used in qsort()
Point p0;

void swap(Point &p1, Point &p2)
{
    Point tmp = p1;
    p1 = p2;
    p2 = tmp;
}

// find orientation of ordered triplet
// 0: p, q, r are collinear
// 1: clockwise
// 2: counterclockwise
int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0; // collinear
    return (val > 0) ? 1 : 2; // clockwise or counterclockwise
}

// square of distance
int distance(Point p1, Point p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) +
           (p1.y - p2.y) * (p1.y - p2.y);
}

int compare(const void *vp1, const void *vp2)
{
    Point *p1 = (Point *)vp1;
    Point *p2 = (Point *)vp2;

    // find orientation
    int val = orientation(p0, *p1, *p2);
    if (val == 0)
    {
        return (distance(p0, *p2) >= distance(p0, *p1)) ? -1 : 1;
    }
    return (val == 2) ? -1 : 1;
}

// prints simple closed path for a set of points
void print_closed_path(Point points[], int n)
{
    // find the bottommost point
    int ymin = points[0].y, min = 0;
    for (int i = 1; i < n; ++i) {
        int y = points[i].y;
        if ((y < ymin) || (ymin == y && points[i].x < points[min].x))
        {
            ymin = points[i].y, min = i;
        }
    }

    // place the bottommost point at first position
    swap(points[0], points[min]);

    // sort n-1 points with respect to first point
    // point p1 comes before p2 in sorted output
    // if p2 has larger polar angle than p1
    p0 = points[0];
    qsort(&points[1], n - 1, sizeof(Point), compare);

    for (int i = 0; i < n; ++i) {
        cout << "(" << points[i].x << ", "
             << points[i].y << "), ";
    }
}

int main() {
    Point points[] = {{0, 3}, {1, 1}, {2, 2}, {4, 4},
                      {0, 0}, {1, 2}, {3, 1}, {3, 3}};

    int n = sizeof(points) / sizeof(points[0]);

    print_closed_path(points, n);

    return 0;
}
