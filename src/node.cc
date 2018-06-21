#include "node.h"
#include "factory.h"
#include "node_base.h"

static Register<mpm::NodeBase<2>, mpm::Node<2, 2, 1>, mpm::Index,
                const Eigen::Matrix<double, 2, 1>&>
    node2d("Node2D");

static Register<mpm::NodeBase<3>, mpm::Node<3, 3, 1>, mpm::Index,
                const Eigen::Matrix<double, 3, 1>&>
    node3d("Node3D");
