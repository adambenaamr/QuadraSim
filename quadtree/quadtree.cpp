#include <cmath>
#include <iostream>

using namespace std;

struct Point
{
  int x;
  int y;

  Point(int x_coord, int y_coord)
  {
    x = x_coord;
    y = y_coord;
  }

  // TODO: Might need to remove
  Point()
  {
    x = 0;
    y = 0;
  }
};

struct Node
{
  Point position;
  int data;

  Node(Point position, int data)
  {
    this->position = position;
    this->data = data;
  }

  // TODO: Might need to remove
  Node()
  {
    data = 0;
  }
};

class QuadTree
{
private:
  Point topLeft;
  Point bottomRight;

  Node *node;

  QuadTree *topLeftTree;
  QuadTree *topRightTree;
  QuadTree *bottomLeftTree;
  QuadTree *bottomRightTree;

public:
  QuadTree()
  {
    topLeft = Point(0, 0);
    bottomRight = Point(0, 0);
    node = NULL;
    topLeftTree = NULL;
    topRightTree = NULL;
    bottomLeftTree = NULL;
    bottomRightTree = NULL;
  }

  QuadTree(Point topLeft, Point bottomRight)
  {
    node = NULL;
    topLeftTree = NULL;
    topRightTree = NULL;
    bottomLeftTree = NULL;
    bottomRightTree = NULL;
    this->topLeft = topLeft;
    this->bottomRight = bottomRight;
  }

  void insert(Node *);

  Node *search(Point);

  bool inBoundary(Point);
  ~QuadTree();
};

// QuadTree::QuadTree()
// {
// }

QuadTree::~QuadTree()
{
}

// Insert a node into a quadtree
void QuadTree::insert(Node *node)
{
  if (node == NULL)
  {
    return;
  }

  if (!inBoundary(node->position))
  {
    return;
  }

  /**
   * We are at a quad of unit area.
   *
   * We cannot subdivide this quadrant further.
   */
  if (abs(topLeft.x - bottomRight.x) <= 1 && abs(topLeft.y - bottomRight.y) <= 1)
  {
    if (node == NULL)
    {
      this->node = node;
    }

    return;
  }

  if ((topLeft.x + bottomRight.x) / 2 >= node->position.x)
  {
    // Indicates topLeftTree
    if ((topLeft.y + bottomRight.y) / 2 >= node->position.y)
    {
      if (topLeftTree == NULL)
      {
        topLeftTree = new QuadTree(Point(topLeft.x, topLeft.y), Point((topLeft.x + bottomRight.x) / 2, (topLeft.y + bottomRight.y) / 2));
      }
      topLeftTree->insert(node);
    }

    // Indicates bottomLeftTree
    else
    {
      if (bottomLeftTree == NULL)
      {
        bottomLeftTree = new QuadTree(Point(topLeft.x, (topLeft.y + bottomRight.y) / 2), Point((topLeft.x + bottomRight.x) / 2, bottomRight.y));
      }

      bottomLeftTree->insert(node);
    }
  }

  else
  {
    // Indicates topRightTree
    if ((topLeft.y + bottomRight.y) / 2 >= node->position.y)
    {
      if (topRightTree == NULL)
      {
        topRightTree = new QuadTree(Point((topLeft.x + bottomRight.x) / 2, topLeft.y), Point(bottomRight.x, (topLeft.y + bottomRight.y) / 2));
      }

      topRightTree->insert(node);
    }

    // Indicates bottomRightTree
    else
    {
      if (bottomRightTree == NULL)
      {
        bottomRightTree = new QuadTree(Point((topLeft.x + bottomRight.x) / 2, (topLeft.y + bottomRight.y) / 2), Point(bottomRight.x, bottomRight.y));
      }

      bottomRightTree->insert(node);
    }
  }
}

// Find a node in a quadtree
Node *QuadTree::search(Point point)
{
  // Current quadrant cannot contain it (the point)
  if (!inBoundary(point))
  {
    return NULL;
  }

  /**
   * We are at a quad of unit lenght.
   *
   * We cannot subdivide this quadrant further.
   */
  if (node != NULL)
  {
    return node;
  }

  if ((topLeft.x + bottomRight.x) / 2 >= point.x)
  {
    // Indicates topLeftTree
    if ((topLeft.y + bottomRight.y) / 2 >= point.y)
    {
      if (topLeftTree == NULL)
      {
        return NULL;
      }

      return topLeftTree->search(point);
    }

    // Indicates bottomLeftTree
    else
    {
      if (bottomLeftTree == NULL)
      {
        return NULL;
      }

      return bottomLeftTree->search(point);
    }
  }

  else
  {
    // Indicates topRightTree
    if ((topLeft.y + bottomRight.y) / 2 >= point.y)
    {
      if (topRightTree == NULL)
      {
        return NULL;
      }

      return topRightTree->search(point);
    }

    // Indicates bottomRightTree
    else
    {
      if (bottomRightTree == NULL)
      {
        return NULL;
      }

      return bottomRightTree->search(point);
    }
  }
}

// Check if current quadrant contains the point
bool QuadTree::inBoundary(Point point)
{
  return (point.x >= topLeft.x && point.x <= bottomRight.x && point.y >= topLeft.y && point.y <= bottomRight.y);
}

// Driver
int main()
{
  QuadTree center(Point(0, 0), Point(8, 8));
  Node a(Point(1, 1), 1);
  Node b(Point(2, 5), 2);
  Node c(Point(7, 6), 3);

  center.insert(&a);
  center.insert(&b);
  center.insert(&c);

  cout << "Node a: " << center.search(Point(1, 1))->data << "\n";
  cout << "Node b: " << center.search(Point(2, 5))->data << "\n";
  cout << "Node c: " << center.search(Point(7, 6))->data << "\n";

  // Non-existing node:
  cout << "Non-existing node: " << center.search(Point(5, 5));

  return 0;
}
