#pragma once

#include "coords_offsetter.hh"

#include <osmium/builder/osm_object_builder.hpp>
#include <osmium/handler.hpp>
#include <osmium/visitor.hpp>

#include <iostream>

class CoordsHandler : public osmium::handler::Handler {

public:
  explicit CoordsHandler(osmium::memory::Buffer& buffer) : m_buffer(buffer) {
  }

  void node(const osmium::Node& node) {
    {
      osmium::builder::NodeBuilder builder{m_buffer};
      copy_attributes(builder, node);
      copy_tags(builder, node.tags());

      auto loc = node.location();

      Coords coords{.x = loc.lon(), .y = loc.lat()};
      CoordsOffsetter::wgs2gcj(&coords);

      loc.set_lon(coords.x);
      loc.set_lat(coords.y);

      builder.set_location(loc);
    }

    m_buffer.commit();
  }

  void way(const osmium::Way& way) {
    {
      osmium::builder::WayBuilder builder{m_buffer};
      copy_attributes(builder, way);
      copy_tags(builder, way.tags());

      builder.add_item(way.nodes());
    }

    m_buffer.commit();
  }

  void relation(const osmium::Relation& relation) {
    {
      osmium::builder::RelationBuilder builder{m_buffer};
      copy_attributes(builder, relation);
      copy_tags(builder, relation.tags());

      builder.add_item(relation.members());
    }

    m_buffer.commit();
  }

  void area(const osmium::Area& area) {
    {
      osmium::builder::AreaBuilder builder{m_buffer};
      builder.initialize_from_object(area);
    }

    m_buffer.commit();
  }

private:
  osmium::memory::Buffer& m_buffer;

  template <typename T>
  void copy_attributes(T& builder, const osmium::OSMObject& object) {
    builder.set_id(object.id())
        .set_deleted(object.deleted())
        .set_visible(object.visible())
        .set_version(object.version())
        .set_changeset(object.changeset())
        .set_timestamp(object.timestamp())
        .set_uid(object.uid())
        .set_user(object.user());
  }

  static void copy_tags(osmium::builder::Builder& parent, const osmium::TagList& tags) {
    osmium::builder::TagListBuilder builder{parent};
    for (const auto& tag : tags) {
      builder.add_tag(tag);
    }
  }
};