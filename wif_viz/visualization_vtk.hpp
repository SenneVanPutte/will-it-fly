#ifndef __VISUALISATION_VTK_HPP_INCLUDED__
#define __VISUALISATION_VTK_HPP_INCLUDED__

#include "visualization.hpp"

//#include <vtkSmartPointer>

#include <iostream>

#include "vtkCubeAxesActor.h"

#include "vtkVersion.h"
#include <vtkSmartPointer.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkPoints.h>
#include <vtkGlyph3D.h>
#include "vtkSmartPointer.h"
#include "vtkFloatArray.h"
#include "vtkPointData.h"
#include "vtkMath.h"
#include "vtkSphereSource.h"
#include "vtkStructuredGrid.h"
#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkArrowSource.h"

#include "vtkPolyDataMapper.h"
#include "vtkProperty.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkInteractorStyleImage.h"
#include "vtkWindowToImageFilter.h"
#include "vtkPNGWriter.h"

namespace wif_viz
{


class visualization_vtk_c : public visualization_c
{
public:
	visualization_vtk_c(std::shared_ptr<flow_c> flow, const vector_2d_c & min_range, const vector_2d_c & max_range);

	virtual ~visualization_vtk_c();

	//
	//virtual void set_velocityarrows(const vector_2d_c & bins);

	virtual void draw(const std::string & filename = "");

private:
	vtkSmartPointer<vtkPoints> construct_points(const vector_2d_c & binning) const;

	vtkSmartPointer<vtkDoubleArray> construct_field(const vector_2d_c & binning, bool scalar) const;

	vtkSmartPointer<vtkStructuredGrid> combine_grid(const vector_2d_c & binning, vtkSmartPointer<vtkPoints> points, vtkSmartPointer<vtkDoubleArray> field) const;

	vtkSmartPointer<vtkStructuredGrid> construct_psi_grid() const;

	vtkSmartPointer<vtkStructuredGrid> construct_phi_grid() const;

	vtkSmartPointer<vtkStructuredGrid> construct_velocity_grid() const;

private:
	std::vector<vtkSmartPointer<vtkActor>> actors;
};


} // namespace wif_viz

#endif // __VISUALISATION_VTK_HPP_INCLUDED__

