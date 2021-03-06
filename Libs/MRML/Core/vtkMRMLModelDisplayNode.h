/*=auto=========================================================================

  Portions (c) Copyright 2005 Brigham and Women's Hospital (BWH) All Rights Reserved.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Program:   3D Slicer
  Module:    $RCSfile: vtkMRMLModelDisplayNode.h,v $
  Date:      $Date: 2006/03/19 17:12:28 $
  Version:   $Revision: 1.6 $

=========================================================================auto=*/

#ifndef __vtkMRMLModelDisplayNode_h
#define __vtkMRMLModelDisplayNode_h

// MRML includes
#include "vtkMRMLDisplayNode.h"

// VTK includes
class vtkAlgorithm;
class vtkAlgorithmOutput;
class vtkAssignAttribute;
class vtkPassThrough;
class vtkPolyData;

/// \brief MRML node to represent a dispaly property of 3D surface model.
///
/// vtkMRMLModelDisplayNode nodes stores display property of a 3D surface model
/// including reference to ColorNode, texture, opacity, etc.
class VTK_MRML_EXPORT vtkMRMLModelDisplayNode : public vtkMRMLDisplayNode
{
public:
  static vtkMRMLModelDisplayNode *New();
  vtkTypeMacro(vtkMRMLModelDisplayNode,vtkMRMLDisplayNode);

  virtual vtkMRMLNode* CreateNodeInstance();

  /// Get node XML tag name (like Volume, Model)
  virtual const char* GetNodeTagName() {return "ModelDisplay";};

  /// Set and observe poly data for this model. It should be the output
  /// polydata of the model node.
#if (VTK_MAJOR_VERSION <= 5)
  virtual void SetInputPolyData(vtkPolyData* polydata);
# else
  virtual void SetInputPolyDataConnection(vtkAlgorithmOutput* polyDataConnection);
  virtual vtkAlgorithmOutput* GetInputPolyDataConnection();
#endif

  /// Return the polydata that was set by SetInputPolyData()
  /// \sa GetOutputPolyData()
  virtual vtkPolyData* GetInputPolyData();

  /// Return the polydata that is processed by the display node.
  /// This is the polydata that needs to be connected with the mappers.
  /// Return 0 if there is no input polydata but it is required.
  /// GetOutputPolyData() should be reimplemented only if the model display
  /// node doesn't take a polydata as input but produce an output polydata.
  /// In all other cases, GetOutputPolyDataConnection() should be reimplemented.
  /// \sa GetInputPolyData(), GetOutputPolyDataConnection()
  virtual vtkPolyData* GetOutputPolyData();
  /// Return the polydata that is processed by the display node.
  /// This is the polydata that needs to be connected with the mappers.
  virtual vtkAlgorithmOutput* GetOutputPolyDataConnection();

  /// Reimplemented to update pipeline with new value
  /// \sa SetActiveAttributeLocation()
  virtual void SetActiveScalarName(const char *scalarName);

  /// Reimplemented to update pipeline with new value
  /// \sa SetActiveScalarName()
  virtual void SetActiveAttributeLocation(int location);

  /// Update the pipeline based on this node attributes
  virtual void UpdatePolyDataPipeline();

  /// Returns true since can apply non linear transforms
  /// \sa ApplyTransformMatrix, ApplyTransform
  virtual bool CanApplyNonLinearTransforms()const {return true;};


protected:
  vtkMRMLModelDisplayNode();
  ~vtkMRMLModelDisplayNode();
  vtkMRMLModelDisplayNode(const vtkMRMLModelDisplayNode&);
  void operator=(const vtkMRMLModelDisplayNode&);

  virtual void ProcessMRMLEvents(vtkObject *caller,
                                 unsigned long event,
                                 void *callData);

  /// To be reimplemented in subclasses if the input of the pipeline changes
#if (VTK_MAJOR_VERSION <= 5)
  virtual void SetInputToPolyDataPipeline(vtkPolyData* polyData);
#else
  virtual void SetInputToPolyDataPipeline(vtkAlgorithmOutput* polyDataConnection);
#endif

  /// Filter that changes the active scalar of the input polydata
  /// using the ActiveScalarName and ActiveAttributeLocation properties.
  /// This can be useful to specify what field array is the color array that
  /// needs to be used by the VTK mappers.
  vtkAssignAttribute* AssignAttribute;

  /// Default filter when assign attribute is not used, e.g ActiveScalarName is
  /// null.
  /// \sa AssignAttribute
  vtkPassThrough* PassThrough;
};

#endif
