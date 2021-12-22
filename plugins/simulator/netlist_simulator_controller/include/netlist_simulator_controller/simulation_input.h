#pragma once

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include "hal_core/defines.h"
#include "hal_core/netlist/boolean_function.h"

namespace hal {
    class Gate;
    class Net;

    class SimulationInputNetEvent : public std::unordered_map<const Net*,BooleanFunction::Value>
    {
        u64 mSimulationDuration;
    public:
        u64 get_simulation_duration() const { return mSimulationDuration; }
        void set_simulation_duration(u64 t) { mSimulationDuration = t; }
    };

    class SimulationInput {

    public:
        struct Clock
        {
            const Net* clock_net;
            u64 switch_time;
            bool start_at_zero;
            u64 period() const { return switch_time * 2; }
        };

    private:
        std::unordered_set<const Gate*> mSimulationSet;
        std::vector<Clock> m_clocks;

        std::unordered_set<const Net*> m_input_nets;
        std::vector<const Net*> m_output_nets;
        std::vector<const Net*> m_partial_nets;

        std::vector<SimulationInputNetEvent> mSimulationInputNetEvents;
        std::string mSaleaeInput;
        u64 mSaleaeTimeScale;

        bool mNoClockUsed;

        void compute_input_nets();
        void compute_output_nets();
        void compute_partial_nets();

    public:
        SimulationInput() : mSaleaeTimeScale(1000000000), mNoClockUsed(false) {;}

        /**
         * Checks whether essential data for simulation has been provided (gates, clock, input_nets)
         * @return true if essential data is present, false otherwise
         */
        bool is_ready() const;

        /**
         * Checks whether gates have been selected for simulation
         * @return true if at least one gate is in simulation set, false otherwise
         */
        bool has_gates() const;

        /**
         * Checks whether a gate is part of the simulation set
         * @param[in] g the gate
         * @return true if part, false otherwise
         */
        bool contains_gate(const Gate* g) const;

        /**
         * Returns the gates from simulation set
         * @return reference to gate set
         */
        const std::unordered_set<const Gate*>& get_gates() const;

        /**
         * Returns the clock(s) set up for simulation
         * @return reference to clock(s)
         */
        const std::vector<Clock>& get_clocks() const { return m_clocks; }

        /**
         * Tests whether net has been selected as clock
         * @param[in] n pointer to net
         * @return true if net has been selected as clock, false otherwise
         */
        bool is_clock(const Net* n) const;

        /**
         * Prepare simulation where no net is defined as clock input
         */
        void set_no_clock_used();

        /**
         * Set input for simulation to saleae file bundle
         * @param[in] filename the filename for CSV file with net <-> binary assignment
         * @param[in] timescale multiplication factor for time value
         */
        void set_saleae_input(const std::string& filename, u64 timescale = 1000000000);

        /**
         * Tests whether net is an input net
         * @param[in] n pointer to net
         * @return true if net is input net, false otherwise
         */
        bool is_input_net(const Net* n) const;

        /**
         * Adds a clock
         * @param[in] clk reference to clock instance
         */
        void add_clock(const Clock& clk);

        /**
         * Add gates to the simulation set that contains all gates that are considered during simulation.
         * This function can only be called before the simulation has been initialized.
         *
         * @param[in] gates - The gates to add.
         */
        void add_gates(const std::vector<Gate*>& gates);

        void clear();

        /**
         * Get all nets that are considered inputs, i.e., not driven by a gate in the simulation set or global inputs.
         *
         * @returns The input nets.
         */
        const std::unordered_set<const Net*>& get_input_nets() const;

        /**
         * Get all output nets of gates in the simulation set that have a destination outside of the set or that are global outputs.
         *
         * @returns The output nets.
         */
        const std::vector<const Net*>& get_output_nets() const;

        /**
         * Get all nets from the partial netlist.
         *
         * @return The nets from partial netlist
         */
        const std::vector<const Net*>& get_partial_netlist_nets() const;

        /**
         * Add single event to simulation input net event vector. This method will be used by controller to setup
         * all events to be simulated prior to call the engines setSimulationInput method.
         *
         * @param[in] ev the simulation input net event
         */
        void add_simulation_net_event(const SimulationInputNetEvent& ev) { mSimulationInputNetEvents.push_back(ev); }

        /**
         * Get all net events setup for simulation
         * @return reference to vector of simulation input net events
         */
        const std::vector<SimulationInputNetEvent>& get_simulation_net_events() const { return mSimulationInputNetEvents; }

        /**
         * Dump content of simulation input instance to file or stderr if no filename given
         * @param filename name of file to be created
         */
        void dump(std::string filename = std::string()) const;

        /**
         * Get SALEAE input file
         * @return Absolute path to CSV file with data <-> net mapping
         */
        std::string get_saleae_input_file() const { return mSaleaeInput; }

        /**
         * Get SALEAE time scale factor
         * @return Scale factor to convert (double) time value stored in file to long integer value
         */
        u64 get_saleae_time_scalefactor() const { return mSaleaeTimeScale; }
    };
}
