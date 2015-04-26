# Makefile demos

demodir :
	mkdir -p ../build/obj/demos

demo_% : export DEMO_NAME = $@
demo_% : demodir
	mkdir -p ../build/obj/demos/$@
	$(MAKE) -C ./$@ demo

demo : viz_demos algo_demos core_demos team_demos

team_demos : team_viz_demos team_core_demos team_algo_demos

# De demos van de viz library
viz_demos :

# De demos van de algo library
algo_demos :

# De demos van de core library
core_demos : demo_core_vector_line demo_core_flow_elements

# De demos van de teams, die eigenlijk niks met onze libraries te maken hebben.
# Hieronder demo's toevoegen als dependancies van de respectievelijke targets!
# Gebruik dezelfde naam als uw directory!

team_viz_demos : vtk_compilatie_demos

team_core_demos : 

team_algo_demos : root_algo_demos gsl_demos

vtk_compilatie_demos : demo_vtk_comp_dolf demo_vtk_comp_kristof demo_vtk_comp_merel demo_vtk_comp_senne

gsl_demos : demo_gsl_integral demo_gsl_diag demo_gsl_andy

root_algo_demos : demo_root_algo_diag