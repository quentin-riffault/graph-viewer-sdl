extern "C" {
    #include "graph_viewer/graph.h"
    #include "graph_viewer/physics.h"
}
#include <gtest/gtest.h>

class PhysicsTest : public testing::Test {
protected:
    PhysicsTest(){
        a = create_node(10);
        b = create_node(20);
        nodelist[0] = a;
        nodelist[1] = b;
        l = create_link(a, b, false, 10);
    }

    ~PhysicsTest(){
        free(a);
        free(b);
        free(l);
    }

    Node* a;
    Node* b;
    Link* l;
    Node* nodelist[2];
};

TEST_F(PhysicsTest, Test_ApplyForces){
    a->pos[0] = 0.0f;
    a->pos[1] = 0.0f;

    b->pos[1] = 1.0f;    
    b->pos[0] = 1.0f;

    
    a->movement_vector[0] =  0.5f;
    a->movement_vector[1] =  0.5f;

    b->movement_vector[0] = -0.5f;
    b->movement_vector[1] = -0.5f;

    
    apply_forces(nodelist, 2, 1/60);

    EXPECT_NEAR(a->pos[0], 0.5, 1e-5);
    EXPECT_NEAR(a->pos[1], 0.5, 1e-5);
    EXPECT_NEAR(a->pos[0], b->pos[0], 1e-5);
    EXPECT_NEAR(a->pos[1], b->pos[1], 1e-5);

    EXPECT_NEAR(a->movement_vector[0], 0.0f, 1e-10);
    EXPECT_NEAR(a->movement_vector[1], 0.0f, 1e-10);
    EXPECT_NEAR(b->movement_vector[0], 0.0f, 1e-10);
    EXPECT_NEAR(b->movement_vector[1], 0.0f, 1e-10);
}

TEST_F(PhysicsTest, Test_DirectionVector){
    vec2 direction = {0.0f};
    
    a->pos[0] = 0.0f;
    a->pos[1] = 0.0f;

    b->pos[1] = 1.0f;
    b->pos[0] = 1.0f;

    compute_direction_vector(a->pos, b->pos, &direction);

    EXPECT_NEAR(direction[0], sqrtf(2)/2, 1e-10);
    EXPECT_NEAR(direction[1], sqrtf(2)/2, 1e-10);
}

TEST_F(PhysicsTest, Test_SpringAttraction){

    a->pos[0] = -0.1f;
    a->pos[1] = -0.1f;

    b->pos[1] = 1.1f;
    b->pos[0] = 1.1f;

    compute_common_attraction(l);
    apply_forces(nodelist, 2, 1/60);

    EXPECT_TRUE(a->pos[0] > -0.1f);
    EXPECT_TRUE(a->pos[1] > -0.1f);

    EXPECT_TRUE(b->pos[0] <  1.1f);
    EXPECT_TRUE(b->pos[1] <  1.1f);
}

TEST_F(PhysicsTest, Test_MagnetRepulsion){
    a->pos[0] = 0.49f;
    a->pos[1] = 0.49f;

    b->pos[1] = 0.51f;
    b->pos[0] = 0.51f;

    compute_common_repulsion(a, b);
    apply_forces(nodelist, 2, 1/60);

    EXPECT_TRUE(a->pos[0] < 0.49f);
    EXPECT_TRUE(a->pos[1] < 0.49f);

    EXPECT_TRUE(b->pos[0] > 0.51f);
    EXPECT_TRUE(b->pos[1] > 0.51f);
}

