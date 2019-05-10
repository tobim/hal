#include "netlist/netlist.h"
#include "netlist/gate.h"
#include "netlist/gate_library/gate_library_manager.h"
#include "netlist/net.h"
#include "netlist/netlist_factory.h"
#include "netlist/module.h"
#include "core/plugin_manager.h"
#include "test_def.h"
#include "gtest/gtest.h"
#include <core/log.h>
#include <iostream>

using namespace gate_library_manager;

class netlist_test : public ::testing::Test
{
protected:
    std::string g_lib_name = "EXAMPLE_GATE_LIBRARY";
    // Minimum id for netlists, gates as well as nets
    const u32 INVALID_GATE_ID = 0;
    const u32 INVALID_NET_ID = 0;
    const u32 INVALID_MODULE_ID = 0;
    const u32 MIN_MODULE_ID = 2;
    const u32 MIN_GATE_ID = 1;
    const u32 MIN_NET_ID = 1;
    const u32 MIN_NETLIST_ID = 1;
    const u32 TOP_MODULE_ID = 1;


    virtual void SetUp()
    {
        //NO_COUT_BLOCK;
        gate_library_manager::load_all();
    }

    virtual void TearDown()
    {
    }

    // TODO: move functions in an own header?
    // Creates an empty netlist with a certain id if passed
    std::shared_ptr<netlist> create_empty_netlist(int id = -1)
    {
        NO_COUT_BLOCK;
        std::shared_ptr<gate_library> gl = get_gate_library(g_lib_name);
        std::shared_ptr<netlist> g_obj   = std::make_shared<netlist>(gl);

        if (id >= 0)
        {
            g_obj->set_id(id);
        }
        return g_obj;
    }

    /*
     *      Example netlist circuit diagram (Id in brackets). Used for get fan in and
     *      out nets.
     *
     *
     *      GND (1) =-= INV (3) =--=             .------= INV (4) =
     *                                 AND2 (0) =-
     *      VCC (2) =--------------=             '------=
     *                                                     AND2 (5) =
     *                                                  =
     *
     *     =                       =           =----------=           =
     *       BUF (6)              ... OR2 (7)             ... OR2 (8)
     *     =                       =           =          =           =
     */

    // Creates a simple netlist shown in the diagram above
    std::shared_ptr<netlist> create_example_netlist(int id = -1)
    {
        NO_COUT_BLOCK;
        std::shared_ptr<gate_library> gl = gate_library_manager::get_gate_library(g_lib_name);
        std::shared_ptr<netlist> nl      = std::make_shared<netlist>(gl);
        if (id >= 0)
        {
            nl->set_id(id);
        }

        // Create the gates
        std::shared_ptr<gate> gate_0 = nl->create_gate(MIN_GATE_ID+0, "AND2", "gate_0");
        std::shared_ptr<gate> gate_1 = nl->create_gate(MIN_GATE_ID+1, "GND", "gate_1");
        std::shared_ptr<gate> gate_2 = nl->create_gate(MIN_GATE_ID+2, "VCC", "gate_2");
        std::shared_ptr<gate> gate_3 = nl->create_gate(MIN_GATE_ID+3, "INV", "gate_3");
        std::shared_ptr<gate> gate_4 = nl->create_gate(MIN_GATE_ID+4, "INV", "gate_4");
        std::shared_ptr<gate> gate_5 = nl->create_gate(MIN_GATE_ID+5, "AND2", "gate_5");
        std::shared_ptr<gate> gate_6 = nl->create_gate(MIN_GATE_ID+6, "BUF", "gate_6");
        std::shared_ptr<gate> gate_7 = nl->create_gate(MIN_GATE_ID+7, "OR2", "gate_7");
        std::shared_ptr<gate> gate_8 = nl->create_gate(MIN_GATE_ID+8, "OR2", "gate_8");

        // Add the nets (net_x_y1_y2... := net between the gate with id x and the gates y1,y2,...)
        std::shared_ptr<net> net_1_3 = nl->create_net(MIN_NET_ID+13, "net_1_3");
        net_1_3->set_src(gate_1, "O");
        net_1_3->add_dst(gate_3, "I");

        std::shared_ptr<net> net_3_0 = nl->create_net(MIN_NET_ID+30, "net_3_0");
        net_3_0->set_src(gate_3, "O");
        net_3_0->add_dst(gate_0, "I0");

        std::shared_ptr<net> net_2_0 = nl->create_net(MIN_NET_ID+20, "net_2_0");
        net_2_0->set_src(gate_2, "O");
        net_2_0->add_dst(gate_0, "I1");

        std::shared_ptr<net> net_0_4_5 = nl->create_net(MIN_NET_ID+045, "net_0_4_5");
        net_0_4_5->set_src(gate_0, "O");
        net_0_4_5->add_dst(gate_4, "I");
        net_0_4_5->add_dst(gate_5, "I0");

        std::shared_ptr<net> net_7_8 = nl->create_net(MIN_NET_ID+78, "net_7_8");
        net_7_8->set_src(gate_7, "O");
        net_7_8->add_dst(gate_8, "I0");

        return nl;
    }

    // Creates an endpoint from a gate and a pin_type
    endpoint get_endpoint(std::shared_ptr<gate> g, std::string pin_type)
    {
        endpoint ep;
        ep.gate     = g;
        ep.pin_type = pin_type;
        return ep;
    }
};

/**
 * Testing the get_shared function which returns a shared_ptr on itselves
 *
 * Functions: get_shared
 */
TEST_F(netlist_test, check_get_shared)
{
    TEST_START
    std::shared_ptr<netlist> nl = create_empty_netlist();
    EXPECT_EQ(nl->get_shared(), nl);
    TEST_END
}

/**
 * Testing the access on the id
 *
 * Functions: get_id, set_id
 */
TEST_F(netlist_test, check_id_access)
{
    TEST_START
    // Create an empty netlist
    std::shared_ptr<netlist> nl = create_empty_netlist();
    // Set the id to another value
    nl->set_id(MIN_NETLIST_ID+123);
    EXPECT_EQ(nl->get_id(), (u32)(MIN_NETLIST_ID+123));
    // Set the id to the same value again
    nl->set_id(MIN_NETLIST_ID+123);
    EXPECT_EQ(nl->get_id(), (u32)(MIN_NETLIST_ID+123));
    TEST_END
}

/**
* Testing the access on the input filename
*
* Functions: get_id, set_id
*/
TEST_F(netlist_test, check_input_filename_access)
{
    TEST_START
    // Create an empty netlist
    std::shared_ptr<netlist> nl = create_empty_netlist();
    // The filename should be empty initially
    EXPECT_EQ(nl->get_input_filename(), hal::path(""));
    // Set a filename
    nl->set_input_filename("/this/is/a/filename");
    EXPECT_EQ(nl->get_input_filename(), hal::path("/this/is/a/filename"));
    // Set the same filename again
    nl->set_input_filename("/this/is/a/filename");
    EXPECT_EQ(nl->get_input_filename(), hal::path("/this/is/a/filename"));
    TEST_END
}

/**
* Testing the access on the design name
*
* Functions: get_design_name, set_design_name
*/
TEST_F(netlist_test, check_design_access)
{
    TEST_START
    // Create an empty netlist
    std::shared_ptr<netlist> nl = create_empty_netlist();
    // The design should be empty initially
    EXPECT_EQ(nl->get_design_name(), "");
    // Set a design name
    nl->set_design_name("design_name");
    EXPECT_EQ(nl->get_design_name(), "design_name");
    // Set the same design name again
    nl->set_design_name("design_name");
    EXPECT_EQ(nl->get_design_name(), "design_name");
    TEST_END
}

/**
* Testing the access on the device name
*
* Functions: get_device_name, set_device_name
*/
TEST_F(netlist_test, check_device_access)
{
    TEST_START
    // Create an empty netlist
    std::shared_ptr<netlist> nl = create_empty_netlist();
    // The design should be empty initially
    EXPECT_EQ(nl->get_device_name(), "");
    // Set a design name
    nl->set_device_name("device_name");
    EXPECT_EQ(nl->get_device_name(), "device_name");
    // Set the same design name again
    nl->set_device_name("device_name");
    EXPECT_EQ(nl->get_device_name(), "device_name");
    TEST_END
}

/**
* Testing the access on the stored pointers of the netlist_internal_manager,
 * the module_manager and the module_manager
*
* Functions: get_gate_library
*/
TEST_F(netlist_test, check_pointer_access)
{
    TEST_START
    // Create an empty netlist
    std::shared_ptr<netlist> nl = create_empty_netlist();
    EXPECT_NE(nl->get_gate_library(), nullptr);
    TEST_END
}

/**
 * Testing the get_unique_gate_id function by creating a netlist with gates of the id
 * 0,1,2,4. The new gate id should be 3.
 *
 * Functions: get_unique_gate_id
 */
TEST_F(netlist_test, check_get_unique_gate_id)
{
    TEST_START
    // Create an empty netlist with some gates
    std::shared_ptr<netlist> nl = create_empty_netlist();
    std::shared_ptr<gate> g_0   = nl->create_gate(MIN_GATE_ID+0, "INV", "gate_0");
    std::shared_ptr<gate> g_1   = nl->create_gate(MIN_GATE_ID+1, "INV", "gate_1");
    std::shared_ptr<gate> g_2   = nl->create_gate(MIN_GATE_ID+3, "INV", "gate_2");
    std::set<u32> used_ids = {MIN_GATE_ID+0,MIN_GATE_ID+1,MIN_GATE_ID+3};

    // Get a unique id
    u32 unique_id = nl->get_unique_gate_id();
    EXPECT_TRUE(used_ids.find(unique_id) == used_ids.end());
    EXPECT_NE(unique_id, INVALID_GATE_ID);

    // Insert the unique id gate and get a new unique id
    std::shared_ptr<gate> g_new   = nl->create_gate(unique_id, "INV", "gate_2");
    used_ids.insert(unique_id);

    unique_id = nl->get_unique_gate_id();
    EXPECT_TRUE(used_ids.find(unique_id) == used_ids.end());
    EXPECT_NE(unique_id, INVALID_GATE_ID);

    // Remove a gate and get a new unique id
    nl->delete_gate(g_1);
    used_ids.erase(MIN_GATE_ID+1);

    unique_id = nl->get_unique_gate_id();
    EXPECT_TRUE(used_ids.find(unique_id) == used_ids.end());
    EXPECT_NE(unique_id, INVALID_GATE_ID);

    TEST_END
}

/**
 * Testing get_num_of_gates function
 *
 * Functions: get_num_of_gates
 */
TEST_F(netlist_test, check_get_num_of_gates)
{
    TEST_START
        // Create an empty netlist with 4 gates
        std::shared_ptr<netlist> nl = create_empty_netlist();
        std::shared_ptr<gate> g_0   = nl->create_gate(nl->get_unique_gate_id(), "INV", "gate_0");
        std::shared_ptr<gate> g_1   = nl->create_gate(nl->get_unique_gate_id(), "INV", "gate_1");
        std::shared_ptr<gate> g_2   = nl->create_gate(nl->get_unique_gate_id(), "INV", "gate_2");
        std::shared_ptr<gate> g_3   = nl->create_gate(nl->get_unique_gate_id(), "INV", "gate_4");

        EXPECT_EQ(nl->get_gates().size(), (size_t)4);

    TEST_END
}

/**
 * Testing addition of gates (calls the function create_gate in netlist_internal_manager)
 *
 * Functions: create_gate
 */
TEST_F(netlist_test, check_add_gate){
TEST_START
{
    // Add a gate the normal way
    std::shared_ptr<netlist> nl = create_empty_netlist();
    std::shared_ptr<gate> g_0 = nl->create_gate(MIN_GATE_ID+0, "INV", "gate_0");
    EXPECT_TRUE(nl->is_gate_in_netlist(g_0));
}
{
    // Add a gate, remove it afterwards and add it again (used to test the free_ids logic)
    std::shared_ptr<netlist> nl = create_empty_netlist();
    std::shared_ptr<gate> g_0 = nl->create_gate(MIN_GATE_ID+0, "INV", "gate_0");
    nl->delete_gate(g_0);
    std::shared_ptr<gate> g_new = nl->create_gate("INV", "gate_0");
    EXPECT_TRUE(nl->is_gate_in_netlist(g_new));
}
// NEGATIVE
{
    // Try to add the same gate twice
    NO_COUT_TEST_BLOCK;
    std::shared_ptr<netlist> nl = create_empty_netlist();
    std::shared_ptr<gate> g_0   = nl->create_gate(MIN_GATE_ID+0, "INV", "gate_0");
    std::shared_ptr<gate> g_1   = nl->create_gate(MIN_GATE_ID+0, "INV", "gate_0");
    EXPECT_NE(g_0, nullptr);
    EXPECT_EQ(g_1, nullptr);
}
/*{

            // Try to add two gates with the same id
            // TODO: Fehler wg. netlist_internal_manager->is_gate_in_netlist
            //NO_COUT_TEST_BLOCK;
            std::shared_ptr<netlist> nl = create_empty_netlist();
            std::shared_ptr<gate> g_0 = nl->create_gate(0, "INV", "gate_0"));
            std::shared_ptr<gate> g_0_other = nl->create_gate(0, "INV", "gate_0_other"));
            nl->create_gate(g_0);
            bool suc = nl->create_gate(g_0_other);
            EXPECT_FALSE(suc);
        }*/
{
    // Try to add a gate with an invalid gate_type
    NO_COUT_TEST_BLOCK;
    std::shared_ptr<netlist> nl = create_empty_netlist();
    std::shared_ptr<gate> g_0   = nl->create_gate(MIN_GATE_ID+0, "invalid_type", "gate_0");
    EXPECT_EQ(g_0, nullptr);
}
{
    // Try to add a gate with an invalid id
    NO_COUT_TEST_BLOCK;
    std::shared_ptr<netlist> nl = create_empty_netlist();
    std::shared_ptr<gate> g_invalid   = nl->create_gate(INVALID_GATE_ID, "INV", "gate_0");
    EXPECT_EQ(g_invalid, nullptr);
}
{
    // Try to add a gate with an invalid name (empty string)
    NO_COUT_TEST_BLOCK;
    std::shared_ptr<netlist> nl = create_empty_netlist();
    std::shared_ptr<gate> g_0   = nl->create_gate(MIN_GATE_ID+0, "INV", "");
    EXPECT_EQ(g_0, nullptr);
}
TEST_END
}

/**
 * Testing deletion of gates (calls the function delete_gate in netlist_internal_manager)
 *
 * Functions: delete_gate
 */
TEST_F(netlist_test, check_delete_gate){
TEST_START
    // POSITIVE
{
    // Add and delete an unconnected gate in a normal way
    std::shared_ptr<netlist> nl = create_empty_netlist();
    std::shared_ptr<gate> g_0 = nl->create_gate(MIN_GATE_ID+0, "INV", "gate_0");
    bool suc                  = nl->delete_gate(g_0);
    EXPECT_TRUE(suc);
    EXPECT_FALSE(nl->is_gate_in_netlist(g_0));
}
{
    // Delete a gate, which is connected to some in and output nets.
    // The nets source and destination should be updated
    std::shared_ptr<netlist> nl  = create_example_netlist();
    std::shared_ptr<gate> gate_0 = nl->get_gate_by_id(MIN_GATE_ID+0);
    bool suc                     = nl->delete_gate(gate_0);
    EXPECT_TRUE(suc);
    NO_COUT_TEST_BLOCK;
    EXPECT_FALSE(nl->get_net_by_id(MIN_NET_ID+30)->is_a_dst(get_endpoint(gate_0, "I0")));
    EXPECT_FALSE(nl->get_net_by_id(MIN_NET_ID+20)->is_a_dst(get_endpoint(gate_0, "I1")));
    EXPECT_EQ(nl->get_net_by_id(MIN_NET_ID+045)->get_src(), get_endpoint(nullptr, ""));
}
{
    // Add and delete global_gnd gate
    std::shared_ptr<netlist> nl = create_empty_netlist();
    std::shared_ptr<gate> g_0   = nl->create_gate(MIN_GATE_ID+0, "GND", "gate_0");
    nl->mark_global_gnd_gate(g_0);
    bool suc = nl->delete_gate(g_0);
    EXPECT_TRUE(suc);
    EXPECT_FALSE(nl->is_gate_in_netlist(g_0));
    EXPECT_TRUE(nl->get_global_gnd_gates().empty());
}
{
    // Add and delete global_vcc gate
    std::shared_ptr<netlist> nl = create_empty_netlist();
    std::shared_ptr<gate> g_0   = nl->create_gate(MIN_GATE_ID+0, "VCC", "gate_0");
    nl->mark_global_vcc_gate(g_0);
    bool suc = nl->delete_gate(g_0);
    EXPECT_TRUE(suc);
    EXPECT_FALSE(nl->is_gate_in_netlist(g_0));
    EXPECT_TRUE(nl->get_global_vcc_gates().empty());
}
// NEGATIVE
{
    // Try to delete a nullptr
    NO_COUT_TEST_BLOCK;
    std::shared_ptr<netlist> nl = create_empty_netlist();
    bool suc                    = nl->delete_gate(nullptr);
    EXPECT_FALSE(suc);
}
{
    // Try to delete a gate which is not part of the netlist
    NO_COUT_TEST_BLOCK;
    std::shared_ptr<netlist> nl = create_empty_netlist();
    std::shared_ptr<gate> g_0   = nl->create_gate(MIN_GATE_ID+0, "INV", "gate_0");
    bool suc                    = nl->delete_gate(g_0);
    EXPECT_TRUE(suc);
}

TEST_END
}

/**
 * Testing the function is_gate_in_netlist
 *
 * Functions: is_gate_in_netlist
 */
TEST_F(netlist_test, check_is_gate_in_netlist){
TEST_START
{
    // Gate is part of the netlist
    std::shared_ptr<netlist> nl = create_empty_netlist();
    std::shared_ptr<gate> g_0 = nl->create_gate(MIN_GATE_ID+0, "INV", "gate_0");
    EXPECT_TRUE(nl->is_gate_in_netlist(g_0));
}
{
    // Gate is not part of the netlist
    std::shared_ptr<netlist> nl = create_empty_netlist();
    std::shared_ptr<gate> g_0   = nl->create_gate(MIN_GATE_ID+0, "INV", "gate_0");
    nl->delete_gate(g_0);
    // Gate isn't added
    EXPECT_FALSE(nl->is_gate_in_netlist(g_0));
}
{
    // Gate is a nullptr
    NO_COUT_TEST_BLOCK;
    std::shared_ptr<netlist> nl = create_empty_netlist();
    EXPECT_FALSE(nl->is_gate_in_netlist(nullptr));
}
TEST_END
}

/**
 * Testing the function get_gate_by_id
 *
 * Functions: get_gate_by_id
 */
TEST_F(netlist_test, check_get_gate_by_id){
TEST_START
{
    // Get (existing) gate with id 3
    std::shared_ptr<netlist> nl = create_empty_netlist();
    std::shared_ptr<gate> g_0 = nl->create_gate(MIN_GATE_ID+3, "INV", "gate_0");
    EXPECT_EQ(nl->get_gate_by_id(MIN_GATE_ID+3), g_0);
}
{
    // Get not existing gate
    NO_COUT_TEST_BLOCK;
    std::shared_ptr<netlist> nl = create_empty_netlist();
    // Gate isn't added
    EXPECT_EQ(nl->get_gate_by_id(MIN_GATE_ID+3), nullptr);
}

TEST_END
}

/**
 * Testing the function get_gates by using a namefilter
 *
 * Functions: get_gates
 */
TEST_F(netlist_test, check_get_gates_by_name){
    TEST_START
        {
            // Get an existing gate of the example netlist by its name
            std::shared_ptr<netlist> nl = create_example_netlist();
            std::shared_ptr<gate> g_0 = nl->get_gate_by_id(MIN_GATE_ID+0);
            std::shared_ptr<gate> g_5 = nl->get_gate_by_id(MIN_GATE_ID+5);
            EXPECT_EQ(nl->get_gates(DONT_CARE, "gate_0"), std::set<std::shared_ptr<gate>>({g_0}));
            EXPECT_EQ(nl->get_gates(DONT_CARE, "gate_5"), std::set<std::shared_ptr<gate>>({g_5}));
        }
        {
            // Call with an non existing gate name
            NO_COUT_TEST_BLOCK;
            std::shared_ptr<netlist> nl = create_empty_netlist();
            EXPECT_EQ(nl->get_gates(DONT_CARE, "not_existing_gate"), std::set<std::shared_ptr<gate>>());
        }
    TEST_END
}

/**
 * Testing the get_gates function using the example netlist (see above). Also tests
 * the get_gate_by_type and the get_gates_by_decorator_type (these functions calls
 * the get_gates function)
 *
 * Functions: get_gates
 */
TEST_F(netlist_test, check_get_gates){
    TEST_START
        {
            // Get all gates of the example netlist
            std::shared_ptr<netlist> nl = create_example_netlist();
            // The expected result
            std::set<std::shared_ptr<gate>> ex_gates;
            for (int id = 0; id <= 8; id++)
            {
                ex_gates.insert(nl->get_gate_by_id(MIN_GATE_ID+id));
            }

            EXPECT_EQ(nl->get_gates(), ex_gates);
        }
        {
            // Get all INV gates of the example netlist
            std::shared_ptr<netlist> nl = create_example_netlist();
            // The expected result
            std::set<std::shared_ptr<gate>> ex_gates = {nl->get_gate_by_id(MIN_GATE_ID+3), nl->get_gate_by_id(MIN_GATE_ID+4)};

            EXPECT_EQ(nl->get_gates("INV"), ex_gates);
            EXPECT_EQ(nl->get_gates("INV"), ex_gates);
        }
    TEST_END
}

/**
 * Testing the addition of global vcc and global gnd gates. The success is
 * verified via the functions get_global_vcc_gates, get_global_gnd_gates,
 * is_global_vcc_gate, is_global_gnd_gate
 *
 * Functions: mark_global_vcc_gate, mark_global_gnd_gate, is_global_vcc_gate
 *           ,is_global_gnd_gate, get_global_vcc_gates, get_global_gnd_gates
 */
TEST_F(netlist_test, check_mark_global_vcc_gate){
    TEST_START
        {
            // Add a global vcc gate which wasn't added to the netlist before
            std::shared_ptr<netlist> nl = create_empty_netlist();

            std::shared_ptr<gate> vcc_gate = nl->create_gate(MIN_GATE_ID+0, "VCC", "gate_vcc");
            bool suc                       = nl->mark_global_vcc_gate(vcc_gate);
            EXPECT_TRUE(suc);
            EXPECT_TRUE(nl->is_global_vcc_gate(vcc_gate));
            EXPECT_EQ(nl->get_global_vcc_gates(), std::set<std::shared_ptr<gate>>({vcc_gate}));
        }
        {
            // Add a global gnd gate which which wasn't added to the netlist before
            std::shared_ptr<netlist> nl = create_empty_netlist();

            std::shared_ptr<gate> gnd_gate = nl->create_gate(MIN_GATE_ID+0, "GND", "gate_gnd");
            bool suc                       = nl->mark_global_gnd_gate(gnd_gate);
            EXPECT_TRUE(suc);
            EXPECT_TRUE(nl->is_global_gnd_gate(gnd_gate));
            EXPECT_EQ(nl->get_global_gnd_gates(), std::set<std::shared_ptr<gate>>({gnd_gate}));
        }
        {
            // Add the same global vcc gate twice
            std::shared_ptr<netlist> nl = create_empty_netlist();

            std::shared_ptr<gate> vcc_gate = nl->create_gate(MIN_GATE_ID+0, "VCC", "gate_vcc");
            nl->mark_global_vcc_gate(vcc_gate);
            bool suc = nl->mark_global_vcc_gate(vcc_gate);
            EXPECT_TRUE(suc);
            EXPECT_TRUE(nl->is_global_vcc_gate(vcc_gate));
            EXPECT_EQ(nl->get_global_vcc_gates(), std::set<std::shared_ptr<gate>>({vcc_gate}));
        }
        {
            // Add the same global gnd gate twice
            std::shared_ptr<netlist> nl = create_empty_netlist();

            std::shared_ptr<gate> gnd_gate = nl->create_gate(MIN_GATE_ID+0, "GND", "gate_gnd");
            nl->mark_global_gnd_gate(gnd_gate);
            bool suc = nl->mark_global_gnd_gate(gnd_gate);
            EXPECT_TRUE(suc);
            EXPECT_TRUE(nl->is_global_gnd_gate(gnd_gate));
            EXPECT_EQ(nl->get_global_gnd_gates(), std::set<std::shared_ptr<gate>>({gnd_gate}));
        }

// NEGATIVE

    TEST_END
}

/**
 * Testing the function get_input_pin_types
 *
 * Functions: get_input_pin_types
 */
TEST_F(netlist_test, check_get_input_pin_types){
    TEST_START
        {
                // Get input pin types of an existing gate type (AND2)
                std::shared_ptr<netlist> nl = create_empty_netlist();
                std::vector<std::string> exp_pin_types = {"I0", "I1"};
                EXPECT_EQ(nl->get_input_pin_types("AND2"), exp_pin_types);
        }
        {
            // Get input type on an non existing gate_type
            std::shared_ptr<netlist> nl            = create_empty_netlist();
            std::vector<std::string> exp_pin_types = {};
            EXPECT_EQ(nl->get_input_pin_types("NEx_PIN"), exp_pin_types);
        }

    TEST_END
}

/**
 * Testing the function get_output_pin_types
 *
 * Functions: get_output_pin_types
 */
TEST_F(netlist_test, check_get_output_pin_types){
    TEST_START
        {
            // Get output pin types of an existing gate type (OR2)
            std::shared_ptr<netlist> nl = create_empty_netlist();
            std::vector<std::string> exp_pin_types = {"Q"};
            EXPECT_EQ(nl->get_output_pin_types("FF"), exp_pin_types);
        }
        {
            // Get output type on an non existing gate_type
            std::shared_ptr<netlist> nl            = create_empty_netlist();
            std::vector<std::string> exp_pin_types = {};
            EXPECT_EQ(nl->get_output_pin_types("NEx_PIN"), exp_pin_types);
        }

    TEST_END
}

/**
 * Testing the function get_inout_pin_types
 *
 * Functions: get_inout_pin_types
 */
/*TEST_F(netlist_test, check_get_inout_pin_types){TEST_START{// Get inout pin types of an existing gate type (IOBUFDS_DCIEN)
                                                           std::shared_ptr<netlist> nl = create_empty_netlist();
std::vector<std::string> exp_pin_types = {"IO", "IOB"};
EXPECT_EQ(nl->get_inout_pin_types("IOBUFDS_DCIEN"), exp_pin_types);
}
{
    // Get inout type on an non existing gate_type
    std::shared_ptr<netlist> nl            = create_empty_netlist();
    std::vector<std::string> exp_pin_types = {};
    EXPECT_EQ(nl->get_inout_pin_types("NEx_PIN"), exp_pin_types);
}

TEST_END
}*/

/**
 * Testing the get_unique_net_id function by creating a netlist with nets of the id
 * 0,1,2,4. The new net id should be 3.
 *
 * Functions: get_unique_net_id
 */
TEST_F(netlist_test, check_get_unique_net_id)
{
    TEST_START
    // Create an empty netlist with some nets
    std::shared_ptr<netlist> nl = create_empty_netlist();
    std::shared_ptr<net> g_0    = nl->create_net(MIN_NET_ID+0, "net_0");
    std::shared_ptr<net> g_1    = nl->create_net(MIN_NET_ID+1, "net_1");
    std::shared_ptr<net> g_4    = nl->create_net(MIN_NET_ID+3, "net_3");

    EXPECT_EQ(nl->get_unique_net_id(), (u32)(MIN_NET_ID+2));

    TEST_END
}

/**
 * Testing get_num_of_nets by call it for the example netlist
 *
 * Functions: get_num_of_nets
 */
TEST_F(netlist_test, check_get_num_of_nets)
{
    TEST_START
    // Create the example netlist (has 5 nets)
    std::shared_ptr<netlist> nl = create_example_netlist();
    EXPECT_EQ(nl->get_nets().size(), (size_t)5);
    TEST_END
}

/**
 * Testing addition of nets (calls the function create_net in netlist_internal_manager).
 * To validate success the function is_net_in_netlist is used.
 *
 * Functions: create_net
 */
TEST_F(netlist_test, check_add_net){
TEST_START
{
    // Add a net the normal way (unrouted)
    std::shared_ptr<netlist> nl = create_empty_netlist();
    std::shared_ptr<net> net_0 = nl->create_net(MIN_NET_ID+0, "net_0");
    EXPECT_NE(net_0, nullptr);
    EXPECT_TRUE(nl->is_net_in_netlist(net_0));
}
    {
        // Add a net, remove it, and add a net with the same id (used to test the free_net_ids logic)
        std::shared_ptr<netlist> nl = create_empty_netlist();
        std::shared_ptr<net> net_0 = nl->create_net(MIN_NET_ID+0, "net_0");
        nl->delete_net(net_0);
        std::shared_ptr<net> net_0_other = nl->create_net(MIN_NET_ID+0, "net_0_other");
        EXPECT_NE(net_0_other, nullptr);
        EXPECT_TRUE(nl->is_net_in_netlist(net_0_other));
    }
// NEGATIVE

    {
        // Create a net with an invalid id
        NO_COUT_TEST_BLOCK;
        std::shared_ptr<netlist> nl = create_empty_netlist();
        std::shared_ptr<net> net_invalid = nl->create_net(INVALID_NET_ID, "net_invalid");
        EXPECT_TRUE(net_invalid == nullptr);
    }
    {
        // Create a net with an already used id
        NO_COUT_TEST_BLOCK;
        std::shared_ptr<netlist> nl = create_empty_netlist();
        std::shared_ptr<net> net_0 = nl->create_net(MIN_NET_ID+0, "net_0");
        std::shared_ptr<net> net_0_other = nl->create_net(MIN_NET_ID+0, "net_0_other");
        EXPECT_TRUE(net_0_other == nullptr);
    }
    {
        // Create a net with an invalid name (empty string)
        NO_COUT_TEST_BLOCK;
        std::shared_ptr<netlist> nl = create_empty_netlist();
        std::shared_ptr<net> net_0 = nl->create_net(MIN_NET_ID+0, "");
        EXPECT_TRUE(net_0 == nullptr);
    }
TEST_END
}

/**
 * Testing deletion of nets (calls the function delete_net in netlist_internal_manager)
 *
 * Functions: delete_net
 */
TEST_F(netlist_test, check_delete_net){
TEST_START
   // POSITIVE
{
    // Add and delete an unrouted net in a normal way
    std::shared_ptr<netlist> nl = create_empty_netlist();
    std::shared_ptr<net> net_0 = nl->create_net(MIN_NET_ID+1, "net_0");
    bool suc                   = nl->delete_net(net_0);
    EXPECT_TRUE(suc);
    EXPECT_FALSE(nl->is_net_in_netlist(net_0));
}
{
    // Delete a net, which isn't unrouted by using the example netlist
    std::shared_ptr<netlist> nl  = create_example_netlist();
    std::shared_ptr<net> net_045 = nl->get_net_by_id(MIN_NET_ID+045);
    bool suc                     = nl->delete_net(net_045);

    EXPECT_TRUE(suc);
    EXPECT_FALSE(nl->is_net_in_netlist(net_045));
    // Check if the netlist was updated correctly
    EXPECT_TRUE(nl->get_gate_by_id(MIN_GATE_ID+1)->get_successors().empty());
    EXPECT_TRUE(nl->get_gate_by_id(MIN_GATE_ID+5)->get_predecessors().empty());
    EXPECT_TRUE(nl->get_gate_by_id(MIN_GATE_ID+6)->get_predecessors().empty());
}
{
    // Delete a global input net
    std::shared_ptr<netlist> nl = create_empty_netlist();
    std::shared_ptr<net> net_0  = nl->create_net(MIN_NET_ID+1, "net_0");
    nl->mark_global_input_net(net_0);
    bool suc = nl->delete_net(net_0);

    EXPECT_TRUE(suc);
    EXPECT_FALSE(nl->is_net_in_netlist(net_0));
    EXPECT_FALSE(nl->is_global_input_net(net_0));
}
{
    // Delete a global output net
    std::shared_ptr<netlist> nl = create_empty_netlist();
    std::shared_ptr<net> net_0  = nl->create_net(MIN_NET_ID+1, "net_0");
    nl->mark_global_output_net(net_0);
    bool suc = nl->delete_net(net_0);

    EXPECT_TRUE(suc);
    EXPECT_FALSE(nl->is_net_in_netlist(net_0));
    EXPECT_FALSE(nl->is_global_output_net(net_0));
}
{
    // Delete a global inout net
    std::shared_ptr<netlist> nl = create_empty_netlist();
    std::shared_ptr<net> net_0  = nl->create_net(MIN_NET_ID+1, "net_0");
    nl->mark_global_inout_net(net_0);
    bool suc = nl->delete_net(net_0);

    EXPECT_TRUE(suc);
    EXPECT_FALSE(nl->is_net_in_netlist(net_0));
    EXPECT_FALSE(nl->is_global_inout_net(net_0));
}
// NEGATIVE
{
    // Try to delete a nullptr
    NO_COUT_TEST_BLOCK;
    std::shared_ptr<netlist> nl = create_empty_netlist();
    bool suc                    = nl->delete_net(nullptr);

    EXPECT_FALSE(suc);
    EXPECT_FALSE(nl->is_net_in_netlist(nullptr));
}
{
    // Try to delete a net which is not part of the netlist
    NO_COUT_TEST_BLOCK;
    std::shared_ptr<netlist> nl = create_empty_netlist();
    std::shared_ptr<net> net_0  = nl->create_net(MIN_NET_ID+1, "net_0");
    // net_0 wasn't added
    bool suc = nl->delete_net(net_0);

    EXPECT_TRUE(suc);
    EXPECT_FALSE(nl->is_net_in_netlist(net_0));
}

TEST_END
}

/**
 * Testing the function is_net_in_netlist
 *
 * Functions: is_net_in_netlist
 */
TEST_F(netlist_test, check_is_net_in_netlist){
TEST_START
{
    // Net is part of the netlist
    std::shared_ptr<netlist> nl = create_empty_netlist();
    std::shared_ptr<net> net_0 = nl->create_net(MIN_NET_ID+1, "net_0");

    EXPECT_TRUE(nl->is_net_in_netlist(net_0));
}

{
    // Net is a nullptr
    NO_COUT_TEST_BLOCK;
    std::shared_ptr<netlist> nl = create_empty_netlist();
    EXPECT_FALSE(nl->is_net_in_netlist(nullptr));
}
TEST_END
}

/**
 * Testing the get_nets function using the example netlist (see above).
 *
 * Functions: get_nets
 */
TEST_F(netlist_test, check_get_nets){
TEST_START
{
    // Get all nets of the example netlist
    std::shared_ptr<netlist> nl = create_example_netlist();
    // The expected result
    std::set<std::shared_ptr<net>> ex_nets;
    for (int id : std::set<int>({MIN_NET_ID+13, MIN_NET_ID+30, MIN_NET_ID+20, MIN_NET_ID+045, MIN_NET_ID+78}))
    {
        ex_nets.insert(nl->get_net_by_id(id));
    }

    EXPECT_EQ(nl->get_nets(), ex_nets);
}
TEST_END
}

/**
 * Testing the function get_net_by_id
 *
 * Functions: get_net_by_id
 */
TEST_F(netlist_test, check_get_net_by_id){
TEST_START
{
    // Net exists (ID: 123)
    std::shared_ptr<netlist> nl = create_empty_netlist();
    std::shared_ptr<net> net_0 = nl->create_net(MIN_NET_ID+123, "net_0");

    EXPECT_EQ(nl->get_net_by_id(MIN_NET_ID+123), net_0);
}
{
    // Net doesn't exists (ID: 123)
    NO_COUT_TEST_BLOCK;
    std::shared_ptr<netlist> nl = create_empty_netlist();
    EXPECT_EQ(nl->get_net_by_id(MIN_NET_ID+123), nullptr);
}

TEST_END
}

/**
 * Testing the function get_nets_by_name
 *
 * Functions: get_nets_by_name
 */
TEST_F(netlist_test, check_get_nets_by_name){
    TEST_START
        {
            // Get an existing net by its name
            std::shared_ptr<netlist> nl = create_empty_netlist();
            std::shared_ptr<net> net_0 = nl->create_net(MIN_NET_ID+0, "net_name");
            std::shared_ptr<net> net_1 = nl->create_net(MIN_NET_ID+1, "other_net_name");

            EXPECT_EQ(nl->get_nets(), std::set<std::shared_ptr<net>>({net_0, net_1}));
            EXPECT_EQ(nl->get_nets("net_name"), std::set<std::shared_ptr<net>>({net_0}));
        }
        {
            // Call with an non existing net name
            NO_COUT_TEST_BLOCK;
            std::shared_ptr<netlist> nl = create_empty_netlist();
            EXPECT_EQ(nl->get_nets("not_existing_net"), std::set<std::shared_ptr<net>>());
        }

    TEST_END
}

/**
 * Testing the addition of global input/output/inout nets. For verification
 * the function is_global_input/output/inout_net is called
 *
 * Functions: mark_global_input_net, mark_global_output_net, mark_global_inout_net
 */
TEST_F(netlist_test, check_add_global_net){
TEST_START
{
    // Add a global input net which isn't part of the netlist yet
    std::shared_ptr<netlist> nl = create_empty_netlist();
    std::shared_ptr<net> net_0 = nl->create_net(MIN_NET_ID+0, "net_0");
    bool suc                   = nl->mark_global_input_net(net_0);

    EXPECT_TRUE(suc);
    EXPECT_TRUE(nl->is_global_input_net(net_0));
}
{
    // Add a global output net which isn't part of the netlist yet
    std::shared_ptr<netlist> nl = create_empty_netlist();
    std::shared_ptr<net> net_0  = nl->create_net(MIN_NET_ID+0, "net_0");
    bool suc                    = nl->mark_global_output_net(net_0);

    EXPECT_TRUE(suc);
    EXPECT_TRUE(nl->is_global_output_net(net_0));
}
{
    // Add a global inout net which isn't part of the netlist yet
    std::shared_ptr<netlist> nl = create_empty_netlist();
    std::shared_ptr<net> net_0  = nl->create_net(MIN_NET_ID+0, "net_0");
    bool suc                    = nl->mark_global_inout_net(net_0);

    EXPECT_TRUE(suc);
    EXPECT_TRUE(nl->is_global_inout_net(net_0));
}
{
    // Add a global input net which was already added (as normal net)
    std::shared_ptr<netlist> nl = create_empty_netlist();
    std::shared_ptr<net> net_0  = nl->create_net(MIN_NET_ID+0, "net_0");
    bool suc                    = nl->mark_global_input_net(net_0);

    EXPECT_TRUE(suc);
    EXPECT_TRUE(nl->is_global_input_net(net_0));
}
{
    // Add a global output net which was already added (as normal net)
    std::shared_ptr<netlist> nl = create_empty_netlist();
    std::shared_ptr<net> net_0  = nl->create_net(MIN_NET_ID+0, "net_0");
    bool suc                    = nl->mark_global_output_net(net_0);

    EXPECT_TRUE(suc);
    EXPECT_TRUE(nl->is_global_output_net(net_0));
}
{
    // Add a global inout net which was already added (as normal net)
    std::shared_ptr<netlist> nl = create_empty_netlist();
    std::shared_ptr<net> net_0  = nl->create_net(MIN_NET_ID+0, "net_0");
    bool suc                    = nl->mark_global_inout_net(net_0);

    EXPECT_TRUE(suc);
    EXPECT_TRUE(nl->is_global_inout_net(net_0));
}
{
    // Add the same global input net twice
    std::shared_ptr<netlist> nl = create_empty_netlist();
    std::shared_ptr<net> net_0  = nl->create_net(MIN_NET_ID+0, "net_0");
    nl->mark_global_input_net(net_0);
    bool suc = nl->mark_global_input_net(net_0);

    EXPECT_TRUE(suc);
    EXPECT_TRUE(nl->is_global_input_net(net_0));
}
{
    // Add the same global output net twice
    std::shared_ptr<netlist> nl = create_empty_netlist();
    std::shared_ptr<net> net_0  = nl->create_net(MIN_NET_ID+0, "net_0");
    nl->mark_global_output_net(net_0);
    bool suc = nl->mark_global_output_net(net_0);

    EXPECT_TRUE(suc);
    EXPECT_TRUE(nl->is_global_output_net(net_0));
}
{
    // Add the same global inout net twice
    std::shared_ptr<netlist> nl = create_empty_netlist();
    std::shared_ptr<net> net_0  = nl->create_net(MIN_NET_ID+0, "net_0");
    nl->mark_global_inout_net(net_0);
    bool suc = nl->mark_global_inout_net(net_0);

    EXPECT_TRUE(suc);
    EXPECT_TRUE(nl->is_global_inout_net(net_0));
}
// NEGATIVE
TEST_END
}

/**
 * Testing the functions is_global_input/output/inout_net. Also tests the access via
 * get_global_input/output/inout_nets
 *
 * Functions: is_global_input_net, is_global_output_net, is_global_inout_net,
 *            get_global_input_nets, get_global_out_nets, get_global_out_nets
 */
TEST_F(netlist_test, check_is_global_net)
{
TEST_START
{
    // The net is a global input net
    std::shared_ptr<netlist> nl = create_empty_netlist();
    std::shared_ptr<net> net_0 = nl->create_net(MIN_NET_ID+0, "net_0");
    nl->mark_global_input_net(net_0);

    EXPECT_TRUE(nl->is_global_input_net(net_0));
    EXPECT_EQ(nl->get_global_input_nets(), std::set<std::shared_ptr<net>>({net_0}));
}
{
    // The net is a global output net
    std::shared_ptr<netlist> nl = create_empty_netlist();
    std::shared_ptr<net> net_0  = nl->create_net(MIN_NET_ID+0, "net_0");
    nl->mark_global_output_net(net_0);

    EXPECT_TRUE(nl->is_global_output_net(net_0));
    EXPECT_EQ(nl->get_global_output_nets(), std::set<std::shared_ptr<net>>({net_0}));
}
{
    // The net is a global inout net
    std::shared_ptr<netlist> nl = create_empty_netlist();
    std::shared_ptr<net> net_0  = nl->create_net(MIN_NET_ID+0, "net_0");
    nl->mark_global_inout_net(net_0);

    EXPECT_TRUE(nl->is_global_inout_net(net_0));
    EXPECT_EQ(nl->get_global_inout_nets(), std::set<std::shared_ptr<net>>({net_0}));
}
{
    // The net isn't a global input net
    std::shared_ptr<netlist> nl = create_empty_netlist();
    std::shared_ptr<net> net_0  = nl->create_net(MIN_NET_ID+0, "net_0");

    EXPECT_FALSE(nl->is_global_input_net(net_0));
    EXPECT_TRUE(nl->get_global_input_nets().empty());
}
{
    // The net isn't a global output net
    std::shared_ptr<netlist> nl = create_empty_netlist();
    std::shared_ptr<net> net_0  = nl->create_net(MIN_NET_ID+0, "net_0");

    EXPECT_FALSE(nl->is_global_output_net(net_0));
    EXPECT_TRUE(nl->get_global_output_nets().empty());
}
{
    // The net isn't a global output net
    std::shared_ptr<netlist> nl = create_empty_netlist();
    std::shared_ptr<net> net_0  = nl->create_net(MIN_NET_ID+1, "net_0");

    EXPECT_FALSE(nl->is_global_inout_net(net_0));
    EXPECT_TRUE(nl->get_global_inout_nets().empty());
}
TEST_END
}


/***************************************************
 *               Module Functions
 *************************************************** /

 /**
 * Testing the get_top_module function
 *
 * Functions: get_top_module
 */
TEST_F(netlist_test, check_get_top_module)
{
    TEST_START
        {
            // Testing the access on the topmodule
            std::shared_ptr<netlist> nl = create_empty_netlist();
            std::shared_ptr<module> tm = nl->get_top_module();
            ASSERT_NE(tm, nullptr);
            EXPECT_EQ(tm->get_parent_module(), nullptr);
            // If only this test fails you may update the TOP_MODULE_ID constant
            EXPECT_EQ(tm->get_id(), TOP_MODULE_ID);
        }
    TEST_END
}

 /**
 * Testing the creation of a module
 *
 * Functions: create_module
 */
TEST_F(netlist_test, check_create_module)
{
    TEST_START
        // Positive
        {
            // Get an existing net by its name
            std::shared_ptr<netlist> nl = create_empty_netlist();
            std::shared_ptr<module> m_0 = nl->create_module(MIN_MODULE_ID+0,"module_0", nl->get_top_module());
            EXPECT_TRUE(nl->is_module_in_netlist(m_0));
        }
        {
            // Add a module, remove it and add a module with the same id (to test the free_module_id logic)
            std::shared_ptr<netlist> nl = create_empty_netlist();
            std::shared_ptr<module> m_0 = nl->create_module(MIN_MODULE_ID+0,"module_0", nl->get_top_module());
            nl->delete_module(m_0);
            std::shared_ptr<module> m_0_other = nl->create_module(MIN_MODULE_ID+0,"module_0_other", nl->get_top_module());
            //EXPECT_FALSE(nl->is_module_in_netlist(m_0)); TODO should be  true
            EXPECT_TRUE(nl->is_module_in_netlist(m_0_other));
        }

        // Negative
        {
            // Create a module with an invalid id
            NO_COUT_TEST_BLOCK;
            std::shared_ptr<netlist> nl = create_empty_netlist();
            std::shared_ptr<module> m_0 = nl->create_module(INVALID_MODULE_ID,"module_0", nl->get_top_module());
            EXPECT_EQ(m_0, nullptr);
        }
        {
            // Create a module with an id, which is already used
            NO_COUT_TEST_BLOCK;
            std::shared_ptr<netlist> nl = create_empty_netlist();
            std::shared_ptr<module> m_0 = nl->create_module(MIN_MODULE_ID+0,"module_0", nl->get_top_module());
            std::shared_ptr<module> m_0_other = nl->create_module(MIN_MODULE_ID+0,"module_0_other", nl->get_top_module());
            EXPECT_EQ(m_0_other, nullptr);
        }
        /*{
            // Create a module with the id, used of the top module TODO: FAILS
            NO_COUT_TEST_BLOCK;
            std::shared_ptr<netlist> nl = create_empty_netlist();
            std::shared_ptr<module> m_0 = nl->create_module(TOP_MODULE_ID,"module_0", nl->get_top_module());
            EXPECT_EQ(m_0, nullptr);
            EXPECT_EQ(nl->get_module_by_id(TOP_MODULE_ID), nl->get_top_module());
        }*/
        {
            // Create a module with an invalid name (empty string)
            NO_COUT_TEST_BLOCK;
            std::shared_ptr<netlist> nl = create_empty_netlist();
            std::shared_ptr<module> m_0 = nl->create_module(MIN_MODULE_ID+0,"", nl->get_top_module());
            EXPECT_EQ(m_0, nullptr);
        }
        {
            // Create a module with no parent-module
            NO_COUT_TEST_BLOCK;
            std::shared_ptr<netlist> nl = create_empty_netlist();
            std::shared_ptr<module> m_0 = nl->create_module(MIN_MODULE_ID+0,"module_0", nullptr);
            EXPECT_EQ(m_0, nullptr);
        }

    TEST_END
}

/**
* Testing the deletion of modules from the netlist. Verification of success by is_module_in_netlist
*
* Functions: delete_module, is_module_in_netlist
*/
TEST_F(netlist_test, check_delete_module)
{
    TEST_START
        // Positive
        {
            // Add a module and delete it after
            std::shared_ptr<netlist> nl = create_empty_netlist();
            std::shared_ptr<module> m_0 = nl->create_module(MIN_MODULE_ID+0, "module_0", nl->get_top_module());
            nl->delete_module(m_0);
            EXPECT_FALSE(nl->is_module_in_netlist(m_0));
        }
        // TODO: more tests (when is_module_in_netlist is fixed)
    TEST_END
}

/**
* Testing the function is_module_in_netlist
*
* Functions: is_module_in_netlist
*/
TEST_F(netlist_test, check_is_module_in_netlist)
{
    TEST_START
        // Positive
        {
            // Add a module and check if it is in the netlist
            std::shared_ptr<netlist> nl = create_empty_netlist();
            std::shared_ptr<module> m_0 = nl->create_module(MIN_MODULE_ID+0, "module_0", nl->get_top_module());
            EXPECT_TRUE(nl->is_module_in_netlist(m_0));
        }
        /*{
            // Create a module, delete it and create a new module with the same id and check if the !old_one! is in the netlist
            // TODO: fails
            std::shared_ptr<netlist> nl = create_empty_netlist();
            std::shared_ptr<module> m_0_old = nl->create_module(MIN_MODULE_ID+0, "module_0_old", nl->get_top_module());
            nl->delete_module(m_0_old);
            std::shared_ptr<module> m_0_other = nl->create_module(MIN_MODULE_ID+0, "module_0_other", nl->get_top_module());
            EXPECT_FALSE(nl->is_module_in_netlist(m_0_old));
        }*/
        // Negative
        /*{
            // Pass a nullptr
            // TODO: fails (SIGSEGV)
            std::shared_ptr<netlist> nl = create_empty_netlist();
            EXPECT_TRUE(nl->is_module_in_netlist(nullptr));
        }*/
    TEST_END
}






