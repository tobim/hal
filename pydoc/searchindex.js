Search.setIndex({docnames:["base_plugin_interface","boolean_function","core_utils","data_container","dataflow","endpoint","gate","gate_library","gate_library_manager","gate_type","graph_algorithm","grouping","gui","gui_plugin_interface","hal_py","hdl_writer_manager","index","module","net","netlist","netlist_factory","netlist_simulator","netlist_utils","path","plugin_manager","plugins"],envversion:{"sphinx.domains.c":1,"sphinx.domains.changeset":1,"sphinx.domains.cpp":1,"sphinx.domains.javascript":1,"sphinx.domains.math":2,"sphinx.domains.python":1,"sphinx.domains.rst":1,"sphinx.domains.std":1,"sphinx.ext.intersphinx":1,"sphinx.ext.todo":1,sphinx:55},filenames:["base_plugin_interface.rst","boolean_function.rst","core_utils.rst","data_container.rst","dataflow.rst","endpoint.rst","gate.rst","gate_library.rst","gate_library_manager.rst","gate_type.rst","graph_algorithm.rst","grouping.rst","gui.rst","gui_plugin_interface.rst","hal_py.rst","hdl_writer_manager.rst","index.rst","module.rst","net.rst","netlist.rst","netlist_factory.rst","netlist_simulator.rst","netlist_utils.rst","path.rst","plugin_manager.rst","plugins.rst"],objects:{"dataflow.DataflowPlugin":{execute:[4,1,1,""],get_name:[4,1,1,""],get_version:[4,1,1,""],name:[4,2,1,""],version:[4,2,1,""]},"graph_algorithm.GraphAlgorithmPlugin":{get_communities:[10,1,1,""],get_communities_fast_greedy:[10,1,1,""],get_communities_multilevel:[10,1,1,""],get_communities_spinglass:[10,1,1,""],get_graph_cut:[10,1,1,""],get_name:[10,1,1,""],get_strongly_connected_components:[10,1,1,""],get_version:[10,1,1,""],name:[10,2,1,""],version:[10,2,1,""]},"hal_gui.GuiApi":{deselect:[12,1,1,""],deselectAllItems:[12,1,1,""],deselectGate:[12,1,1,""],deselectModule:[12,1,1,""],deselectNet:[12,1,1,""],getSelectedGateIds:[12,1,1,""],getSelectedGates:[12,1,1,""],getSelectedItemIds:[12,1,1,""],getSelectedItems:[12,1,1,""],getSelectedModuleIds:[12,1,1,""],getSelectedModules:[12,1,1,""],getSelectedNetIds:[12,1,1,""],getSelectedNets:[12,1,1,""],select:[12,1,1,""],selectGate:[12,1,1,""],selectModule:[12,1,1,""],selectNet:[12,1,1,""]},"hal_py.BasePluginInterface":{get_name:[0,1,1,""],get_version:[0,1,1,""],name:[0,2,1,""],version:[0,2,1,""]},"hal_py.BooleanFunction":{Value:[1,0,1,""],__and__:[1,1,1,""],__call__:[1,1,1,""],__eq__:[1,1,1,""],__iand__:[1,1,1,""],__init__:[1,1,1,""],__invert__:[1,1,1,""],__ior__:[1,1,1,""],__ixor__:[1,1,1,""],__ne__:[1,1,1,""],__or__:[1,1,1,""],__str__:[1,1,1,""],__xor__:[1,1,1,""],evaluate:[1,1,1,""],from_string:[1,3,1,""],get_dnf_clauses:[1,1,1,""],get_truth_table:[1,1,1,""],get_variables:[1,1,1,""],is_constant_one:[1,1,1,""],is_constant_zero:[1,1,1,""],is_dnf:[1,1,1,""],is_empty:[1,1,1,""],optimize:[1,1,1,""],substitute:[1,1,1,""],to_dnf:[1,1,1,""],variables:[1,2,1,""]},"hal_py.BooleanFunction.Value":{name:[1,2,1,""]},"hal_py.CoreUtils":{get_base_directory:[2,5,1,""],get_binary_directory:[2,5,1,""],get_default_log_directory:[2,5,1,""],get_gate_library_directories:[2,5,1,""],get_library_directory:[2,5,1,""],get_plugin_directories:[2,5,1,""],get_share_directory:[2,5,1,""],get_user_config_directory:[2,5,1,""],get_user_share_directory:[2,5,1,""]},"hal_py.DataContainer":{data:[3,2,1,""],delete_data:[3,1,1,""],get_data:[3,1,1,""],get_data_map:[3,1,1,""],set_data:[3,1,1,""]},"hal_py.Endpoint":{__init__:[5,1,1,""],gate:[5,2,1,""],get_gate:[5,1,1,""],get_net:[5,1,1,""],get_pin:[5,1,1,""],is_destination:[5,2,1,""],is_destination_pin:[5,1,1,""],is_source:[5,2,1,""],is_source_pin:[5,1,1,""],net:[5,2,1,""],pin:[5,2,1,""]},"hal_py.GUIPluginInterface":{exec:[13,1,1,""]},"hal_py.Gate":{add_boolean_function:[6,1,1,""],boolean_functions:[6,2,1,""],data:[6,2,1,""],delete_data:[6,1,1,""],fan_in_nets:[6,2,1,""],fan_out_nets:[6,2,1,""],get_boolean_function:[6,1,1,""],get_boolean_functions:[6,1,1,""],get_data:[6,1,1,""],get_data_map:[6,1,1,""],get_fan_in_endpoint:[6,1,1,""],get_fan_in_endpoints:[6,1,1,""],get_fan_in_net:[6,1,1,""],get_fan_in_nets:[6,1,1,""],get_fan_out_endpoint:[6,1,1,""],get_fan_out_endpoints:[6,1,1,""],get_fan_out_net:[6,1,1,""],get_fan_out_nets:[6,1,1,""],get_grouping:[6,1,1,""],get_id:[6,1,1,""],get_input_pins:[6,1,1,""],get_location:[6,1,1,""],get_location_x:[6,1,1,""],get_location_y:[6,1,1,""],get_module:[6,1,1,""],get_name:[6,1,1,""],get_netlist:[6,1,1,""],get_output_pins:[6,1,1,""],get_predecessor:[6,1,1,""],get_predecessors:[6,1,1,""],get_successor:[6,1,1,""],get_successors:[6,1,1,""],get_type:[6,1,1,""],get_unique_predecessors:[6,1,1,""],get_unique_successors:[6,1,1,""],has_location:[6,1,1,""],id:[6,2,1,""],input_pins:[6,2,1,""],is_gnd_gate:[6,1,1,""],is_vcc_gate:[6,1,1,""],location:[6,2,1,""],location_x:[6,2,1,""],location_y:[6,2,1,""],mark_gnd_gate:[6,1,1,""],mark_vcc_gate:[6,1,1,""],module:[6,2,1,""],name:[6,2,1,""],netlist:[6,2,1,""],output_pins:[6,2,1,""],predecessors:[6,2,1,""],set_data:[6,1,1,""],set_location:[6,1,1,""],set_location_x:[6,1,1,""],set_location_y:[6,1,1,""],set_name:[6,1,1,""],successors:[6,2,1,""],type:[6,2,1,""],unique_predecessors:[6,2,1,""],unique_successors:[6,2,1,""],unmark_gnd_gate:[6,1,1,""],unmark_vcc_gate:[6,1,1,""]},"hal_py.GateLibrary":{__init__:[7,1,1,""],add_include:[7,1,1,""],contains_gate_type:[7,1,1,""],contains_gate_type_by_name:[7,1,1,""],create_gate_type:[7,1,1,""],gate_types:[7,2,1,""],get_gate_type_by_name:[7,1,1,""],get_gate_types:[7,1,1,""],get_gnd_gate_types:[7,1,1,""],get_includes:[7,1,1,""],get_name:[7,1,1,""],get_path:[7,1,1,""],get_vcc_gate_types:[7,1,1,""],gnd_gate_types:[7,2,1,""],includes:[7,2,1,""],mark_gnd_gate_type:[7,1,1,""],mark_vcc_gate_type:[7,1,1,""],name:[7,2,1,""],path:[7,2,1,""],vcc_gate_types:[7,2,1,""]},"hal_py.GateType":{BaseType:[9,0,1,""],ClearPresetBehavior:[9,0,1,""],PinDirection:[9,0,1,""],PinType:[9,0,1,""],__init__:[9,1,1,""],add_boolean_function:[9,1,1,""],add_boolean_functions:[9,1,1,""],add_input_pin:[9,1,1,""],add_input_pins:[9,1,1,""],add_output_pin:[9,1,1,""],add_output_pins:[9,1,1,""],add_pin:[9,1,1,""],add_pins:[9,1,1,""],assign_pin_group:[9,1,1,""],assign_pin_type:[9,1,1,""],base_type:[9,2,1,""],boolean_functions:[9,2,1,""],config_data_category:[9,2,1,""],config_data_identifier:[9,2,1,""],gate_library:[9,2,1,""],get_base_type:[9,1,1,""],get_boolean_functions:[9,1,1,""],get_clear_preset_behavior:[9,1,1,""],get_config_data_category:[9,1,1,""],get_config_data_identifier:[9,1,1,""],get_gate_library:[9,1,1,""],get_id:[9,1,1,""],get_input_pins:[9,1,1,""],get_name:[9,1,1,""],get_output_pins:[9,1,1,""],get_pin_direction:[9,1,1,""],get_pin_directions:[9,1,1,""],get_pin_groups:[9,1,1,""],get_pin_type:[9,1,1,""],get_pin_types:[9,1,1,""],get_pins:[9,1,1,""],get_pins_of_direction:[9,1,1,""],get_pins_of_group:[9,1,1,""],get_pins_of_type:[9,1,1,""],id:[9,2,1,""],input_pins:[9,2,1,""],is_lut_init_ascending:[9,1,1,""],lut_init_ascending:[9,2,1,""],name:[9,2,1,""],output_pins:[9,2,1,""],pin_directions:[9,2,1,""],pin_groups:[9,2,1,""],pin_types:[9,2,1,""],pins:[9,2,1,""],set_clear_preset_behavior:[9,1,1,""],set_config_data_category:[9,1,1,""],set_config_data_identifier:[9,1,1,""],set_lut_init_ascending:[9,1,1,""]},"hal_py.GateType.BaseType":{name:[9,2,1,""]},"hal_py.GateType.ClearPresetBehavior":{name:[9,2,1,""]},"hal_py.GateType.PinDirection":{name:[9,2,1,""]},"hal_py.GateType.PinType":{name:[9,2,1,""]},"hal_py.Grouping":{assign_gate:[11,1,1,""],assign_gate_by_id:[11,1,1,""],assign_module:[11,1,1,""],assign_module_by_id:[11,1,1,""],assign_net:[11,1,1,""],assign_net_by_id:[11,1,1,""],contains_gate:[11,1,1,""],contains_gate_by_id:[11,1,1,""],contains_module:[11,1,1,""],contains_module_by_id:[11,1,1,""],contains_net:[11,1,1,""],contains_net_by_id:[11,1,1,""],gate_ids:[11,2,1,""],gates:[11,2,1,""],get_gate_ids:[11,1,1,""],get_gates:[11,1,1,""],get_id:[11,1,1,""],get_module_ids:[11,1,1,""],get_modules:[11,1,1,""],get_name:[11,1,1,""],get_net_ids:[11,1,1,""],get_netlist:[11,1,1,""],get_nets:[11,1,1,""],id:[11,2,1,""],module_ids:[11,2,1,""],modules:[11,2,1,""],name:[11,2,1,""],net_ids:[11,2,1,""],netlist:[11,2,1,""],nets:[11,2,1,""],remove_gate:[11,1,1,""],remove_gate_by_id:[11,1,1,""],remove_module:[11,1,1,""],remove_module_by_id:[11,1,1,""],remove_net:[11,1,1,""],remove_net_by_id:[11,1,1,""],set_name:[11,1,1,""]},"hal_py.HalPath":{__init__:[23,1,1,""],__str__:[23,1,1,""]},"hal_py.Module":{assign_gate:[17,1,1,""],contains_gate:[17,1,1,""],contains_module:[17,1,1,""],data:[17,2,1,""],delete_data:[17,1,1,""],gates:[17,2,1,""],get_data:[17,1,1,""],get_data_map:[17,1,1,""],get_gate_by_id:[17,1,1,""],get_gates:[17,1,1,""],get_grouping:[17,1,1,""],get_id:[17,1,1,""],get_input_nets:[17,1,1,""],get_input_port_name:[17,1,1,""],get_input_port_names:[17,1,1,""],get_input_port_net:[17,1,1,""],get_internal_nets:[17,1,1,""],get_name:[17,1,1,""],get_netlist:[17,1,1,""],get_next_input_port_id:[17,1,1,""],get_next_output_port_id:[17,1,1,""],get_output_nets:[17,1,1,""],get_output_port_name:[17,1,1,""],get_output_port_names:[17,1,1,""],get_output_port_net:[17,1,1,""],get_parent_module:[17,1,1,""],get_submodules:[17,1,1,""],get_type:[17,1,1,""],id:[17,2,1,""],input_nets:[17,2,1,""],input_port_names:[17,2,1,""],internal_nets:[17,2,1,""],name:[17,2,1,""],netlist:[17,2,1,""],next_input_port_id:[17,2,1,""],next_output_port_id:[17,2,1,""],output_nets:[17,2,1,""],output_port_names:[17,2,1,""],parent_module:[17,2,1,""],remove_gate:[17,1,1,""],set_data:[17,1,1,""],set_input_port_name:[17,1,1,""],set_name:[17,1,1,""],set_next_input_port_id:[17,1,1,""],set_next_output_port_id:[17,1,1,""],set_output_port_name:[17,1,1,""],set_parent_module:[17,1,1,""],set_type:[17,1,1,""],submodules:[17,2,1,""],type:[17,2,1,""]},"hal_py.Net":{add_destination:[18,1,1,""],add_source:[18,1,1,""],data:[18,2,1,""],delete_data:[18,1,1,""],destinations:[18,2,1,""],get_data:[18,1,1,""],get_data_map:[18,1,1,""],get_destinations:[18,1,1,""],get_grouping:[18,1,1,""],get_id:[18,1,1,""],get_name:[18,1,1,""],get_netlist:[18,1,1,""],get_num_of_destinations:[18,1,1,""],get_num_of_sources:[18,1,1,""],get_source:[18,1,1,""],get_sources:[18,1,1,""],id:[18,2,1,""],is_a_destination:[18,1,1,""],is_a_source:[18,1,1,""],is_global_input_net:[18,1,1,""],is_global_output_net:[18,1,1,""],is_unrouted:[18,1,1,""],mark_global_input_net:[18,1,1,""],mark_global_output_net:[18,1,1,""],name:[18,2,1,""],netlist:[18,2,1,""],num_of_destinations:[18,2,1,""],num_of_sources:[18,2,1,""],remove_destination:[18,1,1,""],remove_source:[18,1,1,""],set_data:[18,1,1,""],set_name:[18,1,1,""],sources:[18,2,1,""],unmark_global_input_net:[18,1,1,""],unmark_global_output_net:[18,1,1,""]},"hal_py.Netlist":{clear_caches:[19,1,1,""],create_gate:[19,1,1,""],create_grouping:[19,1,1,""],create_module:[19,1,1,""],create_net:[19,1,1,""],delete_gate:[19,1,1,""],delete_grouping:[19,1,1,""],delete_module:[19,1,1,""],delete_net:[19,1,1,""],design_name:[19,2,1,""],device_name:[19,2,1,""],gate_library:[19,2,1,""],gates:[19,2,1,""],get_design_name:[19,1,1,""],get_device_name:[19,1,1,""],get_free_gate_ids:[19,1,1,""],get_free_grouping_ids:[19,1,1,""],get_free_module_ids:[19,1,1,""],get_free_net_ids:[19,1,1,""],get_gate_by_id:[19,1,1,""],get_gate_library:[19,1,1,""],get_gates:[19,1,1,""],get_global_input_nets:[19,1,1,""],get_global_output_nets:[19,1,1,""],get_gnd_gates:[19,1,1,""],get_grouping_by_id:[19,1,1,""],get_groupings:[19,1,1,""],get_id:[19,1,1,""],get_input_filename:[19,1,1,""],get_module_by_id:[19,1,1,""],get_modules:[19,1,1,""],get_net_by_id:[19,1,1,""],get_nets:[19,1,1,""],get_next_gate_id:[19,1,1,""],get_next_grouping_id:[19,1,1,""],get_next_module_id:[19,1,1,""],get_next_net_id:[19,1,1,""],get_top_module:[19,1,1,""],get_unique_gate_id:[19,1,1,""],get_unique_grouping_id:[19,1,1,""],get_unique_module_id:[19,1,1,""],get_unique_net_id:[19,1,1,""],get_used_gate_ids:[19,1,1,""],get_used_grouping_ids:[19,1,1,""],get_used_module_ids:[19,1,1,""],get_used_net_ids:[19,1,1,""],get_vcc_gates:[19,1,1,""],global_input_nets:[19,2,1,""],global_output_nets:[19,2,1,""],gnd_gates:[19,2,1,""],groupings:[19,2,1,""],id:[19,2,1,""],input_filename:[19,2,1,""],is_gate_in_netlist:[19,1,1,""],is_global_input_net:[19,1,1,""],is_global_output_net:[19,1,1,""],is_gnd_gate:[19,1,1,""],is_grouping_in_netlist:[19,1,1,""],is_module_in_netlist:[19,1,1,""],is_net_in_netlist:[19,1,1,""],is_vcc_gate:[19,1,1,""],mark_global_input_net:[19,1,1,""],mark_global_output_net:[19,1,1,""],mark_gnd_gate:[19,1,1,""],mark_vcc_gate:[19,1,1,""],modules:[19,2,1,""],nets:[19,2,1,""],set_design_name:[19,1,1,""],set_device_name:[19,1,1,""],set_free_gate_ids:[19,1,1,""],set_free_grouping_ids:[19,1,1,""],set_free_module_ids:[19,1,1,""],set_free_net_ids:[19,1,1,""],set_id:[19,1,1,""],set_input_filename:[19,1,1,""],set_next_gate_id:[19,1,1,""],set_next_grouping_id:[19,1,1,""],set_next_module_id:[19,1,1,""],set_next_net_id:[19,1,1,""],set_used_gate_ids:[19,1,1,""],set_used_grouping_ids:[19,1,1,""],set_used_module_ids:[19,1,1,""],set_used_net_ids:[19,1,1,""],top_module:[19,2,1,""],unmark_global_input_net:[19,1,1,""],unmark_global_output_net:[19,1,1,""],unmark_gnd_gate:[19,1,1,""],unmark_vcc_gate:[19,1,1,""],vcc_gates:[19,2,1,""]},"hal_py.NetlistFactory":{create_netlist:[20,5,1,""],load_netlist:[20,5,1,""],load_netlists:[20,5,1,""]},"hal_py.NetlistUtils":{copy_netlist:[22,5,1,""],get_nets_at_pins:[22,5,1,""],get_next_sequential_gates:[22,5,1,""],get_subgraph_function:[22,5,1,""],remove_buffers:[22,5,1,""],remove_unused_lut_endpoints:[22,5,1,""],rename_luts_according_to_function:[22,5,1,""]},"hal_py.hdl_writer_manager":{get_cli_options:[15,5,1,""],write:[15,5,1,""]},"hal_py.plugin_manager":{get_plugin_instance:[24,5,1,""],get_plugin_names:[24,5,1,""],load:[24,5,1,""],load_all_plugins:[24,5,1,""],unload:[24,5,1,""],unload_all_plugins:[24,5,1,""]},"netlist_simulator.Event":{__eq__:[21,1,1,""],__init__:[21,1,1,""],__lt__:[21,1,1,""],affected_net:[21,2,1,""],id:[21,2,1,""],new_value:[21,2,1,""],time:[21,2,1,""]},"netlist_simulator.NetlistSimulator":{add_clock_frequency:[21,1,1,""],add_clock_period:[21,1,1,""],add_gates:[21,1,1,""],generate_vcd:[21,1,1,""],get_gates:[21,1,1,""],get_input_nets:[21,1,1,""],get_output_nets:[21,1,1,""],get_simulation_state:[21,1,1,""],get_simulation_timeout:[21,1,1,""],load_initial_values:[21,1,1,""],load_initial_values_from_netlist:[21,1,1,""],reset:[21,1,1,""],set_input:[21,1,1,""],set_iteration_timeout:[21,1,1,""],set_simulation_state:[21,1,1,""],simulate:[21,1,1,""]},"netlist_simulator.NetlistSimulatorPlugin":{create_simulator:[21,1,1,""],get_name:[21,1,1,""],get_version:[21,1,1,""],name:[21,2,1,""],version:[21,2,1,""]},"netlist_simulator.SignalValue":{name:[21,2,1,""]},"netlist_simulator.Simulation":{__init__:[21,1,1,""],add_event:[21,1,1,""],get_events:[21,1,1,""],get_net_value:[21,1,1,""]},dataflow:{DataflowPlugin:[4,0,1,""]},graph_algorithm:{GraphAlgorithmPlugin:[10,0,1,""]},hal_gui:{GuiApi:[12,0,1,""]},hal_py:{BasePluginInterface:[0,0,1,""],BooleanFunction:[1,0,1,""],CoreUtils:[2,4,0,"-"],DataContainer:[3,0,1,""],Endpoint:[5,0,1,""],GUIPluginInterface:[13,0,1,""],Gate:[6,0,1,""],GateLibrary:[7,0,1,""],GateLibraryManager:[8,2,1,""],GateType:[9,0,1,""],Grouping:[11,0,1,""],HalPath:[23,0,1,""],Module:[17,0,1,""],Net:[18,0,1,""],Netlist:[19,0,1,""],NetlistFactory:[20,4,0,"-"],NetlistUtils:[22,4,0,"-"],hdl_writer_manager:[15,4,0,"-"],plugin_manager:[24,4,0,"-"]},netlist_simulator:{Event:[21,0,1,""],NetlistSimulator:[21,0,1,""],NetlistSimulatorPlugin:[21,0,1,""],SignalValue:[21,0,1,""],Simulation:[21,0,1,""]}},objnames:{"0":["py","class","Python class"],"1":["py","method","Python method"],"2":["py","attribute","Python attribute"],"3":["py","staticmethod","Python static method"],"4":["py","module","Python module"],"5":["py","function","Python function"]},objtypes:{"0":"py:class","1":"py:method","2":"py:attribute","3":"py:staticmethod","4":"py:module","5":"py:function"},terms:{"1st":6,"2nd":6,"boolean":[6,7,9,14,22],"case":[7,9,21,22],"class":[0,1,3,4,5,6,7,9,10,11,12,13,17,18,19,21,23],"default":[2,9,19,24],"function":[2,6,7,9,12,14,18,19,20,22,23,24],"int":[4,6,9,10,11,12,17,18,19,21,22],"new":[1,6,7,11,17,18,19,20,21],"return":[0,1,2,3,4,5,6,7,9,10,11,12,13,15,17,18,19,20,21,22,24],"static":[1,2],"switch":4,"true":[1,3,5,6,7,9,11,12,13,15,17,18,19,21,22,24],"try":2,AND:1,For:[9,17],IDs:[10,11,19,22],NOT:1,ONE:[1,21],The:[0,1,2,3,4,5,6,7,9,10,11,12,13,15,17,18,19,20,21,22,24],Use:[2,18,21],Useful:21,__and__:1,__call__:1,__eq__:[1,21],__iand__:1,__init__:[1,5,7,9,21,23],__invert__:1,__ior__:1,__ixor__:1,__lt__:21,__ne__:1,__or__:1,__str__:[1,23],__xor__:1,abort:[18,21],about:[6,9,18,19],abov:22,accur:[5,9],act:11,activ:9,add:[3,6,7,9,17,18,19,21],add_boolean_funct:[6,9],add_clock_frequ:21,add_clock_period:21,add_destin:18,add_ev:21,add_gat:21,add_includ:7,add_input_pin:9,add_output_pin:9,add_pin:9,add_sourc:18,added:[9,12,17,21],address:9,advanc:21,affect:21,affected_net:21,algorithm:[1,25],alia:8,all:[1,3,6,7,9,11,12,17,18,19,21,22,24],allow:11,alphabet:1,alreadi:11,also:[1,17],alwai:1,analysi:25,ani:11,anoth:[1,11,17],api:25,appli:[1,11,17,19,21],applic:19,arg0:[1,21,23],arg:[1,12,18,19,20,22,23],ascend:9,assign:[6,9,11,17,18,19],assign_g:[11,17],assign_gate_by_id:11,assign_modul:11,assign_module_by_id:11,assign_net:11,assign_net_by_id:11,assign_pin_group:9,assign_pin_typ:9,associ:[3,5,6,9,11,17,18,19,21,24],automat:[17,19],avail:6,base:[2,6,7,9,14,17,18],base_typ:[7,9],baseplugininterfac:[0,24],basetyp:[7,9],basic:24,been:[9,19],befor:[1,9,12,21],beforehand:9,behavior:9,being:10,belong:9,better:22,between:21,binari:2,bit:[1,9],bool:[1,3,4,5,6,7,9,11,12,13,15,17,18,19,21,22,24],boolean_funct:[6,9],booleanfunct:[1,6,9,22],both:[1,9,21],bracket:1,buffer:22,bunction:1,cach:[19,22],call:[9,13,19,24],callabl:[6,11,17,18,19],camera:12,can:[1,6,9,10,11,17,18,19,21],carri:21,categori:[3,6,9,17,18],caus:21,cell:10,chang:[9,17],channel:[3,6,17,18],check:[1,5,6,7,11,17,18,19],claus:1,clear:[9,12,19],clear_cach:19,clear_current_select:12,clearpresetbehavior:9,clock:[9,21],clock_net:21,cluster:10,collect:[7,11],combin:[1,9,22],combinatori:9,command:15,commun:10,compon:10,compris:[1,5],condit:[11,17,19],config:2,config_data_categori:9,config_data_identifi:9,configur:[2,9],connect:[5,6,10,11,22],consid:[21,22],constant:[1,6],construct:[1,7,21],contain:[1,2,6,7,9,11,14,17,18,19],contains_g:[11,17],contains_gate_by_id:11,contains_gate_typ:7,contains_gate_type_by_nam:7,contains_modul:[11,17],contains_module_by_id:11,contains_net:11,contains_net_by_id:11,content:16,contrast:11,control:21,convert:1,coordin:[6,19],copi:22,copy_netlist:22,core:16,coreutil:2,correspond:[7,17],cp1:9,cp2:9,creat:[4,7,19,20,21],create_g:19,create_gate_typ:7,create_group:19,create_modul:19,create_net:19,create_netlist:20,create_simul:21,current:[2,12,19,21],custom:21,cut:10,cycl:21,dana:25,data:[6,9,14,17,18],data_typ:[3,6,17,18],datacontain:[3,6,17,18],dataflow:25,dataflowplugin:4,deep:22,defin:[6,9,15],delet:[3,6,17,18],delete_data:[3,6,17,18],delete_g:19,delete_group:19,delete_modul:19,delete_net:19,deprec:18,depth:10,describ:[1,7,9],deselect:12,deselectallitem:12,deselectg:12,deselectmodul:12,deselectnet:12,design:[11,19],design_nam:19,desir:24,destin:[5,17,18,21],determin:[2,12],devic:19,device_nam:19,dict:[1,3,6,7,9,10,17,18,21,22],dictionari:[6,17],differ:22,direct:[6,9,17],directori:[2,24],directory_nam:24,disabl:21,disjunct:1,dispatch:15,distanc:10,divice_nam:19,dnf:1,doe:[9,11,21],draw_graph:4,driven:[18,21],dsp:9,durat:21,dure:[1,11,21],each:[1,10,11,17,20],edg:21,either:[9,17],element:[18,21],empti:[1,6,18,20,22,24],enabl:[9,17],end:21,end_tim:21,endpoint:[6,14,18,22],entir:22,entiti:[3,11],entri:[3,6,17,18],environ:2,equal:[1,21],error:[1,18,19],especi:21,evalu:1,event:[3,6,17,18,21],ever:19,exampl:[1,6],exec:13,execut:[2,4],exist:[3,6,9,12,17,18],explicit:[3,6,17,18],explicitli:19,explor:11,exponenti:1,express:1,extens:22,extract:1,factori:14,fail:11,fals:[1,3,5,6,7,9,11,12,17,18,19,21,22,24],fan:[6,22],fan_in_net:6,fan_out_net:6,fast:10,faster:18,file:[2,7,15,19,20,21,24],file_nam:15,file_path:24,filenam:19,fill:22,filter:[6,11,17,18,19],find:[2,9,22],first:[1,6,17,18],fit:12,flip:10,flop:10,follow:19,forc:[3,6,11,17,18],form:1,format:15,found:[1,17,22],fpga:21,framework:24,free:17,freed:19,frequenc:21,from:[1,3,4,6,7,9,10,11,17,18,19,20,21,22],from_str:1,func:6,further:10,gate:[2,4,5,10,11,12,14,17,18,19,20,21,22],gate_id:[11,12,19],gate_librari:[9,19,20],gate_library_fil:20,gate_typ:[6,7,19],gatelibrari:[7,9,19,20],gatelibrarymanag:8,gatetyp:[6,7,9,19],gener:[4,9,13,21,22],generate_vcd:21,gerner:21,get:[0,1,2,3,4,5,6,7,9,10,11,12,17,18,19,21,22,24],get_base_directori:2,get_base_typ:9,get_binary_directori:2,get_boolean_funct:[6,9],get_clear_preset_behavior:9,get_cli_opt:15,get_commun:10,get_communities_fast_greedi:10,get_communities_multilevel:10,get_communities_spinglass:10,get_config_data_categori:9,get_config_data_identifi:9,get_data:[3,6,17,18],get_data_map:[3,6,17,18],get_default_log_directori:2,get_design_nam:19,get_destin:18,get_device_nam:19,get_dnf_claus:1,get_ev:21,get_fan_in_endpoint:6,get_fan_in_net:6,get_fan_out_endpoint:6,get_fan_out_net:6,get_free_gate_id:19,get_free_grouping_id:19,get_free_module_id:19,get_free_net_id:19,get_gat:[5,10,11,17,19,21],get_gate_by_id:[17,19],get_gate_id:11,get_gate_librari:[9,19],get_gate_library_directori:2,get_gate_typ:7,get_gate_type_by_nam:7,get_global_input_net:19,get_global_output_net:19,get_gnd_gat:19,get_gnd_gate_typ:7,get_graph_cut:10,get_group:[6,17,18,19],get_grouping_by_id:19,get_id:[6,9,11,17,18,19],get_includ:7,get_input_filenam:19,get_input_net:[17,21],get_input_pin:[6,9],get_input_port_nam:17,get_input_port_net:17,get_internal_net:17,get_library_directori:2,get_loc:6,get_location_i:6,get_location_x:6,get_modul:[6,11,19],get_module_by_id:19,get_module_id:11,get_nam:[0,4,6,7,9,10,11,17,18,21],get_net:[5,11,19],get_net_by_id:19,get_net_id:11,get_net_valu:21,get_netlist:[6,11,17,18],get_nets_at_pin:22,get_next_gate_id:19,get_next_grouping_id:19,get_next_input_port_id:17,get_next_module_id:19,get_next_net_id:19,get_next_output_port_id:17,get_next_sequential_g:22,get_num_of_destin:18,get_num_of_sourc:18,get_output_net:[17,21],get_output_pin:[6,9],get_output_port_nam:17,get_output_port_net:17,get_parent_modul:17,get_path:7,get_pin:[5,9],get_pin_direct:9,get_pin_group:9,get_pin_typ:9,get_pins_of_direct:9,get_pins_of_group:9,get_pins_of_typ:9,get_plugin_directori:2,get_plugin_inst:24,get_plugin_nam:24,get_predecessor:6,get_share_directori:2,get_simulation_st:21,get_simulation_timeout:21,get_sourc:18,get_strongly_connected_compon:10,get_subgraph_funct:22,get_submodul:17,get_successor:[6,22],get_top_modul:19,get_truth_t:1,get_typ:[6,17],get_unique_gate_id:19,get_unique_grouping_id:19,get_unique_module_id:19,get_unique_net_id:19,get_unique_predecessor:6,get_unique_successor:6,get_used_gate_id:19,get_used_grouping_id:19,get_used_module_id:19,get_used_net_id:19,get_user_config_directori:2,get_user_share_directori:2,get_vari:1,get_vcc_gat:19,get_vcc_gate_typ:7,get_vers:[0,4,10,21],getselectedg:12,getselectedgateid:12,getselecteditem:12,getselecteditemid:12,getselectedmodul:12,getselectedmoduleid:12,getselectednet:12,getselectednetid:12,given:[1,3,6,7,9,17,18,19,20,21],global:[6,17,18,19,21],global_input_net:19,global_output_net:19,gnd:[6,7,19],gnd_gate:19,gnd_gate_typ:7,graph:[4,12,25],graph_algorithm:10,graphalgorithmplugin:10,greedi:10,ground:9,group:[4,6,9,14,17,18,19,22],grouping_id:19,gui:[3,6,14,17,18,25],guiapi:12,guiplugininterfac:13,hal:[2,5,6,9,15,16,17,18,19,20,21,22,24],hal_base_path:2,hal_fil:20,hal_gui:12,hal_path:[2,7,15,19,20,21,24],hal_pi:[0,1,2,3,4,5,6,7,8,9,10,11,12,13,15,17,18,19,20,21,22,23,24],halpath:[2,7,15,19,20,21,23,24],handl:[1,9,21],happen:21,has:[9,17,18],has_loc:6,have:[9,19,21],hdl:[2,14],hdl_file:20,hdl_writer_manag:15,help:[5,9],hertz:21,hierarch:[11,17],high:[4,21],highest:19,hold:3,home:2,identifi:[4,9],ids:[12,19],igraph:10,imped:21,implement:22,improv:22,inc:7,includ:[1,6,7,9,17,18,19,21,22],index:[9,10,16],index_to_pin:9,indic:9,indirect:17,infinit:21,influenc:[21,22],info:[3,6,17,18],inform:[6,9,18,19],initi:[5,9,21,22,24],inout:9,input:[1,5,6,9,15,17,18,19,21,22],input_filenam:19,input_net:17,input_pin:[6,9],input_port_nam:17,inspect:21,instal:2,instanc:[1,7,21],instead:18,intend:1,interfac:[14,15,24],intern:[9,17,19,21],internal_net:17,interpret:[1,2],invalid:[9,19],invert:9,io_pad:9,is_a_destin:18,is_a_sourc:18,is_constant_on:1,is_constant_zero:1,is_destin:5,is_destination_pin:5,is_dnf:1,is_empti:1,is_gate_in_netlist:19,is_global_input_net:[18,19],is_global_output_net:[18,19],is_gnd_gat:[6,19],is_grouping_in_netlist:19,is_input:22,is_lut_init_ascend:9,is_module_in_netlist:19,is_net_in_netlist:19,is_sourc:5,is_source_pin:5,is_unrout:18,is_vcc_gat:[6,19],item:12,iter:21,its:[2,6,7,9,17,18,19,22,24],itself:22,kei:[3,6,17,18],known:1,kwarg:[1,12,18,19,20,22,23],lambda:[6,11,17,18,19],latch:9,layout:6,least:[1,17],leav:[6,18],len:18,level:[3,4,6,17,18],libnetlist_simul:21,librari:[2,9,14,19,20],like:6,limit:10,line:15,list:[1,2,4,6,7,9,10,11,12,15,17,18,19,20,21,22,24],load:[20,21,24],load_all_plugin:24,load_initial_valu:21,load_initial_values_from_netlist:21,load_netlist:20,local:2,locat:6,location_i:6,location_x:6,log:[2,3,6,17,18],log_with_info_level:[3,6,17,18],logic:[1,21,22],look:22,loop:21,loos:17,lut:[9,22],lut_init_ascend:9,mai:[3,6,11,17,18,21,22],make:[9,22],manag:14,map:[6,9,17,21],mark:[6,7,18,19],mark_global_input_net:[18,19],mark_global_output_net:[18,19],mark_gnd_gat:[6,19],mark_gnd_gate_typ:7,mark_vcc_gat:[6,19],mark_vcc_gate_typ:7,match:[1,11,17,19,20],maximum:21,mccluskei:1,member:[1,9,21],memori:10,might:1,mnetid:12,modifi:12,modul:[6,11,12,14,16,19,22],module_id:[11,12,19],most:1,move:17,multi:18,multilevel:10,multipl:[6,9],must:[1,9],name:[0,1,4,5,6,7,9,10,11,17,18,19,21,24],navigate_to_select:12,need:11,neg:6,neg_stat:9,negat:[1,9],net:[5,6,11,12,14,17,19,21,22],net_id:[11,12,19],netlist:[3,4,6,7,10,11,13,14,15,17,18,25],netlist_simul:21,netlistfactori:20,netlistsimul:21,netlistsimulatorplugin:21,netlistutil:22,new_par:17,new_valu:21,new_variable_nam:1,next:[17,19],next_input_port_id:17,next_output_port_id:17,none:[1,6,7,9,11,12,17,18,19,20,21,22,23],normal:1,nullptr:19,num_of_destin:18,num_of_sourc:18,number:[1,10,18,21],object:[2,7,13],off:4,old:[1,17],old_variable_nam:1,one:[1,6,11,17,21,22],onli:[6,11,17,19,21],only_custom_funct:6,oper:[1,4,10],optim:1,option:15,order:[1,9],ordered_vari:1,other:[17,21,22],otherwis:[1,2,3,5,6,7,9,11,17,18,19,20,21,22,24],out:[6,18,22],output:[1,5,6,9,17,18,19,21,22],output_net:17,output_path:4,output_pin:[6,9],output_port_nam:17,outsid:[17,21],overload:[1,12,18,19,20,22,23],overwrit:[3,6,11,17,18],pad:9,page:16,pair:1,param:[1,6,12,18,19,20,22],paramet:[1,2,3,4,6,7,9,10,11,13,15,17,18,19,20,21,22,24],parent:[2,17,19],parent_modul:17,pars:[1,7],part:[1,7,21],pass:12,path:[2,4,7,14,19,20,21,24],perform:22,period:21,physic:6,picosecond:21,pin:[5,6,7,9,18,22],pin_direct:9,pin_group:9,pin_nam:9,pin_typ:9,pindirect:9,pintyp:9,place:1,plain:1,plugin:[2,4,10,14,16,21],plugin_manag:24,plugin_nam:24,point:[10,21],port:[6,17],port_nam:17,posit:[6,12],potenti:[6,18],power:9,pre:20,preced:1,predecessor:[6,22],present:22,preset:9,previou:[11,12,17],previous:19,print:18,priorit:4,process:[17,21],programopt:15,provid:[2,21,22],python3:2,quin:1,ram:9,recommend:22,recurs:17,recus:17,reflect:22,regard:[6,17],regist:[4,19],rel:2,relat:11,releas:24,relev:21,remov:[1,11,17,18,19,21,22],remove_buff:22,remove_destin:18,remove_g:[11,17],remove_gate_by_id:11,remove_modul:11,remove_module_by_id:11,remove_net:11,remove_net_by_id:11,remove_sourc:18,remove_unknown_vari:1,remove_unused_lut_endpoint:22,renam:[1,22],rename_luts_according_to_funct:22,replac:1,repres:[1,6,9,10,19,21],represent:1,requir:[7,19],reserv:19,reset:[6,9,21],resourc:24,respect:[5,6],ressourc:24,result:[1,11,17,19,22],rise:21,rtype:[1,18,19,20,22],run:[10,13],runtim:1,rytp:9,same:9,scc:10,scroll:12,search:[2,16,17,24],see:[5,9],select:[9,12],selectg:12,selectmodul:12,selectnet:12,self:[0,1,3,4,5,6,7,9,10,11,12,13,17,18,19,21,23],sequenti:[9,21,22],set:[6,9,10,11,15,17,18,19,21,22,24],set_clear_preset_behavior:9,set_config_data_categori:9,set_config_data_identifi:9,set_data:[3,6,17,18],set_design_nam:19,set_device_nam:19,set_free_gate_id:19,set_free_grouping_id:19,set_free_module_id:19,set_free_net_id:19,set_id:19,set_input:21,set_input_filenam:19,set_input_port_nam:17,set_iteration_timeout:21,set_loc:6,set_location_i:6,set_location_x:6,set_lut_init_ascend:9,set_nam:[6,11,17,18],set_next_gate_id:19,set_next_grouping_id:19,set_next_input_port_id:17,set_next_module_id:19,set_next_net_id:19,set_next_output_port_id:17,set_output_port_nam:17,set_parent_modul:17,set_simulation_st:21,set_typ:17,set_used_gate_id:19,set_used_grouping_id:19,set_used_module_id:19,set_used_net_id:19,shall:22,share:2,should:[4,22],show:12,signal:21,signalvalu:21,signatur:[5,9],signific:1,simpl:22,simul:25,sinc:[1,18,19,21],singl:[1,11,21,24],size:4,some:17,sort:[17,21],sourc:[2,5,17,18],source_fil:2,spare:19,specif:[6,10,21,22],specifi:[3,6,7,9,10,11,17,18,19,20,21,22,24],spin:10,spinglass:10,ssc:10,start:[4,10,21],start_at_zero:21,start_tim:21,startup:21,state:[9,21],std:9,store:[3,6,11,17,18],str:[0,1,3,4,5,6,7,9,10,11,15,17,18,19,20,21,22,23,24],string:[1,9],strongli:10,subgraph:22,subgraph_g:22,submodul:17,subset:22,substitut:1,succ:19,success:[3,6,7,9,11,13,15,17,18,19,20,21,24],successor:[6,22],suppli:[1,6,18],support:[1,21],sure:9,tabl:1,take:21,target:[15,19,22],temporarili:11,term:1,termin:10,terminal_gate_typ:10,test:21,than:18,therefor:17,thi:[1,6,7,9,11,17,18,19,21,22],thu:1,time:[9,17,21],timefram:21,timeout:21,to_dnf:1,toggl:9,top:[17,19],top_modul:19,trace:[3,6,17,18],travers:22,treat:21,tri:4,truth:1,tupl:[1,3,6,9,12,17,18],turn:4,two:[1,21],typ:9,type:[0,1,2,3,4,5,6,7,10,11,12,13,14,15,17,18,19,20,21,22,24],typic:19,undefin:[1,21],underli:19,unequ:1,uniqu:[6,9,11,17,18,19,21,24],unique_predecessor:6,unique_successor:6,unix:2,unknown:[6,21],unload:24,unload_all_plugin:24,unmark:[6,18,19],unmark_global_input_net:[18,19],unmark_global_output_net:[18,19],unmark_gnd_g:[6,19],unmark_vcc_g:[6,19],unrout:18,unstructur:11,until:22,usag:22,use:[2,22],used:[1,6,9,19,22],user:[2,9],using:[1,6,20,22],usual:6,util:[1,14],valid:6,valu:[1,3,6,9,17,18,19,21,22],variabl:[1,2,22],variable_nam:1,variant:22,vcc:[6,7,19],vcc_gate:19,vcc_gate_typ:7,vcd:21,vector:[1,2,17],verilog:15,version:[0,4,10,18,21,22],vhdl:[7,15],via:6,view:12,wai:11,walk:1,warn:[1,18],well:[9,17,19],were:6,when:[1,9,21],where:[2,4],whether:[1,5,6,7,11,17,18,19,21],which:[1,6,9,10,12,17,18,22],which_pin:6,wire:21,within:[7,11,17,19,21,22],word:22,write:[15,21],writer:14,written:4,xor:1,zero:[1,21],zoom:12},titles:["Base Plugin Interface","Boolean Function","Core Utils","Data Container","Dataflow Analysis (DANA)","Endpoint","Gate","Gate Library","Gate Library Manager","Gate Type","Graph Algorithms","Grouping","GUI API","GUI Plugin Interface","HAL Core Documentation","HDL Writer Manager","hal_py Documentation","Module","Net","Netlist","Netlist Factory","Netlist Simulator","Netlist Utils","HAL Path","Plugin Manager","HAL Plugins Documentation"],titleterms:{"boolean":1,"function":1,algorithm:10,analysi:4,api:12,base:0,contain:3,core:[2,14],dana:4,data:3,dataflow:4,document:[14,16,25],endpoint:5,factori:20,gate:[6,7,8,9],graph:10,group:11,gui:[12,13],hal:[14,23,25],hal_pi:16,hdl:15,indic:16,interfac:[0,13],librari:[7,8],manag:[8,15,24],modul:17,net:18,netlist:[19,20,21,22],path:23,plugin:[0,13,24,25],simul:21,tabl:16,type:9,util:[2,22],writer:15}})