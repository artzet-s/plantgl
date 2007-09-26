/* -*-c++-*-
 *  ----------------------------------------------------------------------------
 *
 *       PlantGL: The Plant Graphic Library
 *
 *       Copyright 1995-2007 UMR CIRAD/INRIA/INRA DAP 
 *
 *       File author(s): F. Boudon et al.
 *
 *  ----------------------------------------------------------------------------
 *
 *                      GNU General Public Licence
 *
 *       This program is free software; you can redistribute it and/or
 *       modify it under the terms of the GNU General Public License as
 *       published by the Free Software Foundation; either version 2 of
 *       the License, or (at your option) any later version.
 *
 *       This program is distributed in the hope that it will be useful,
 *       but WITHOUT ANY WARRANTY; without even the implied warranty of
 *       MERCHANTABILITY or FITNESS For A PARTICULAR PURPOSE. See the
 *       GNU General Public License for more details.
 *
 *       You should have received a copy of the GNU General Public
 *       License along with this program; see the file COPYING. If not,
 *       write to the Free Software Foundation, Inc., 59
 *       Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 *  ----------------------------------------------------------------------------
 */


/*! \file scne_shape.h
    \brief Definition of the scene class Shape3D and Shape.
*/


#ifndef __scne_shape_h__
#define __scne_shape_h__

/* ----------------------------------------------------------------------- */

#include <plantgl/scenegraph/core/sceneobject.h>

#include <plantgl/scenegraph/geometry/geometry.h>
#include <plantgl/scenegraph/appearance/material.h>

/* ----------------------------------------------------------------------- */

PGL_BEGIN_NAMESPACE

/* ----------------------------------------------------------------------- */

/**
    \class Shape3D
    \brief A Shape is composed of a Geometry object and an Appearance object.
      There is an optional id to identy the shape. We use it when
      building a Scene from AMAPmod to store the id of the corresponding
      Vertex.
*/

/* ------------------------------------------------------------------------- */

class SG_API Shape3D : public SceneObject
{
public:

  /** A structure which helps to build a Shape3D when parsing.
      Fields are normally allocated while parsing and are free when the
      object is contructed using the member \c destroy. */

    struct SG_API Builder : public SceneObject::Builder {

            /// A constructor. It inits all the pointers to null.
            Builder( );

            /// A destructor.
            virtual ~Builder( );

            /** Returns a pointer to a SceneObject constructed using the values
                contained within \e self. If \e self is not valid, it returns a
                null pointer. */
            virtual SceneObjectPtr build( ) = 0;
    };

  /// Default constructor.
  Shape3D( ) ;

  /// Destructor
  virtual ~Shape3D() ;


  /** Applies the action \e action to \e self.
      For each shape within \e self, it applies the action first to the
      Geometry part and second to the Appearance part. */
    virtual bool applyGeometryFirst( Action& action ) = 0 ;

  /** Applies the action \e action to \e self.
      It applies the action to the Geometry part only. The Appearance part
      is skipped. */
    virtual bool applyGeometryOnly( Action& action ) = 0 ;

   /** Applies the action \e action to \e self.
      It applies the action first to the Appearance part and second to the
      Geometry part. */
   virtual bool applyAppearanceFirst( Action& action ) = 0 ;

  /** Applies the action \e action to \e self.
      It applies the action to the Appearance part only. The Geometry
      part is skipped. */
    virtual bool applyAppearanceOnly( Action& action ) = 0;

    /// Prints \e s to the output stream \e stream.
//    friend ostream& operator<<( ostream& stream, Shape3D& s );

}; // class Shape3D

/// Shape3D Pointer
typedef RCPtr<Shape3D> Shape3DPtr;

/* ------------------------------------------------------------------------- */

/**
    \class Shape
    \brief A Shape is composed of a Geometry object and an Appearance object.
      There is an optional id to identy the shape. We use it when
      building a Scene from AMAPmod to store the id of the corresponding
      Vertex.
*/
class SG_API Shape : public Shape3D
{

public:

  /** A structure which helps to build a Geometry when parsing.
      Fields are normally allocated while parsing and are free when the
      object is contructed using the member \c destroy. */

    struct SG_API Builder : public Shape3D::Builder {

            /// A constructor. It inits all the pointers to null.
            Builder( );

            /// A destructor.
            virtual ~Builder( );

            /** Returns a pointer to a Geometry constructed using the values
                contained within \e self. If \e self is not valid, it returns a
                null pointer. */
            virtual SceneObjectPtr build( );

            /// Destroys all the pointers self contains.
            virtual void destroy( );

            /// Returns whether self is valid.
            virtual bool isValid( ) const;

            /// A pointer to the \b appearance field.
            AppearancePtr * Appearance;

            /// A pointer to the \b geometry field.
            GeometryPtr * Geometry;

            /// A pointer to the \b identification field.
            uint32_t * Id;
    };

  /// The undef value for the Id field.
  static const uint32_t NOID;

  /// Default constructor.
  Shape( );

  /** Constructs a Shape with the Geometry \e _geom, the Appearance
      \e _app and the id \e _id. */
  Shape( const GeometryPtr& _geom,
             const AppearancePtr& _app = Material::DEFAULT_MATERIAL,
             uint32_t _id=NOID);

  /** Constructs a Shape with the Geometry \e _geom, the Appearance
      \e _app and the id \e _id. */
  Shape( const std::string&   name,
		 const GeometryPtr&   geom,
	     const AppearancePtr& app = Material::DEFAULT_MATERIAL,
         uint32_t id = NOID );

  /// Destructor
  virtual ~Shape();

  /// Set computed names to \e self , geometry and apperance.
  void setComputedName();

  /// Returns whether \e self is valid.
  virtual bool isValid( ) const;

    /// Applies the action \e action to \e self.
  virtual bool apply( Action& action );

  /// Deep copy of \e this.
  virtual SceneObjectPtr copy() const ;

  virtual bool applyGeometryFirst( Action& action );

  virtual bool applyGeometryOnly( Action& action );

  virtual bool applyAppearanceFirst( Action& action );

  virtual bool applyAppearanceOnly( Action& action );

  /// Return the Geometry of \e self.
  const GeometryPtr& getGeometry() const;

  /// Return the Geometry of \e self.
  GeometryPtr& getGeometry();

  /// Return the Appearance of \e self.
  const AppearancePtr& getAppearance() const;

  /// Return the Appearance of \e self.
  AppearancePtr& getAppearance();

  /// Return the Id of \e self.
  virtual uint32_t getId() const;

  /// Return the Id of \e self.
  uint32_t& getId();

  /// The appearance of \e self.
  AppearancePtr appearance;

  /// The geometry of \e self.
  GeometryPtr geometry;

  /// The identification id of \e self.
  uint32_t id;

}; // class Shape

/// Shape Pointer
typedef RCPtr<Shape> ShapePtr;


/* ------------------------------------------------------------------------- */

// __geom_geometry_h__
/* ----------------------------------------------------------------------- */

PGL_END_NAMESPACE

/* ----------------------------------------------------------------------- */
#endif

