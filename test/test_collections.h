
UFBXT_FILE_TEST(max_selection_sets)
#if UFBXT_IMPL
{
	ufbx_node *node = ufbx_find_node(scene, "Box001");
	ufbxt_assert(node && node->mesh);
	ufbx_mesh *mesh = node->mesh;

	{
		ufbx_selection_set *set = (ufbx_selection_set*)ufbx_find_element(scene, UFBX_ELEMENT_SELECTION_SET, "ObjectCube");
		ufbxt_assert(set && set->nodes.count == 1);
		ufbx_selection_node *sel = set->nodes.data[0];
		ufbxt_assert(sel->target_node == node && sel->target_mesh == mesh);
		ufbxt_assert(sel->include_node);
		ufbxt_assert(sel->vertices.count == 0);
		ufbxt_assert(sel->edges.count == 0);
		ufbxt_assert(sel->faces.count == 0);
	}

	{
		ufbx_selection_set *set = (ufbx_selection_set*)ufbx_find_element(scene, UFBX_ELEMENT_SELECTION_SET, "Box001_TopFace_Face");
		ufbxt_assert(set && set->nodes.count == 1);
		ufbx_selection_node *sel = set->nodes.data[0];
		ufbxt_assert(sel->target_node == node && sel->target_mesh == mesh);
		ufbxt_assert(!sel->include_node);
		ufbxt_assert(sel->vertices.count == 0);
		ufbxt_assert(sel->edges.count == 0);
		ufbxt_assert(sel->faces.count == 2);

		for (size_t i = 0; i < sel->faces.count; i++) {
			ufbx_face face = mesh->faces[sel->faces.data[i]];
			for (size_t j = 0; j < face.num_indices; j++) {
				ufbx_vec3 pos = ufbx_get_vertex_vec3(&mesh->vertex_position, face.index_begin + j);
				pos = ufbx_transform_position(&node->geometry_to_world, pos);
				ufbxt_assert_close_real(err, pos.y / 10.0f, 2.0f);
			}
		}
	}

	{
		ufbx_selection_set *set = (ufbx_selection_set*)ufbx_find_element(scene, UFBX_ELEMENT_SELECTION_SET, "Box001_BottomFace_Face");
		ufbxt_assert(set && set->nodes.count == 1);
		ufbx_selection_node *sel = set->nodes.data[0];
		ufbxt_assert(sel->target_node == node && sel->target_mesh == mesh);
		ufbxt_assert(!sel->include_node);
		ufbxt_assert(sel->vertices.count == 0);
		ufbxt_assert(sel->edges.count == 0);
		ufbxt_assert(sel->faces.count == 2);

		for (size_t i = 0; i < sel->faces.count; i++) {
			ufbx_face face = mesh->faces[sel->faces.data[i]];
			for (size_t j = 0; j < face.num_indices; j++) {
				ufbx_vec3 pos = ufbx_get_vertex_vec3(&mesh->vertex_position, face.index_begin + j);
				pos = ufbx_transform_position(&node->geometry_to_world, pos);
				ufbxt_assert_close_real(err, pos.y / 10.0f, 0.0f);
			}
		}
	}

	{
		ufbx_selection_set *set = (ufbx_selection_set*)ufbx_find_element(scene, UFBX_ELEMENT_SELECTION_SET, "Box001_SideFaces_Face");
		ufbxt_assert(set && set->nodes.count == 1);
		ufbx_selection_node *sel = set->nodes.data[0];
		ufbxt_assert(sel->target_node == node && sel->target_mesh == mesh);
		ufbxt_assert(!sel->include_node);
		ufbxt_assert(sel->vertices.count == 0);
		ufbxt_assert(sel->edges.count == 0);
		ufbxt_assert(sel->faces.count == 8);

		for (size_t i = 0; i < sel->faces.count; i++) {
			ufbx_face face = mesh->faces[sel->faces.data[i]];
			ufbx_real avg = 0.0f;
			for (size_t j = 0; j < face.num_indices; j++) {
				ufbx_vec3 pos = ufbx_get_vertex_vec3(&mesh->vertex_position, face.index_begin + j);
				pos = ufbx_transform_position(&node->geometry_to_world, pos);
				avg += pos.y;
			}
			avg /= (ufbx_real)face.num_indices * 10.0f;
			ufbxt_assert(avg > 0.5f && avg < 1.5f); 
		}
	}

	{
		ufbx_selection_set *set = (ufbx_selection_set*)ufbx_find_element(scene, UFBX_ELEMENT_SELECTION_SET, "Box001_TopEdges_Edge");
		ufbxt_assert(set && set->nodes.count == 1);
		ufbx_selection_node *sel = set->nodes.data[0];
		ufbxt_assert(sel->target_node == node && sel->target_mesh == mesh);
		ufbxt_assert(!sel->include_node);
		ufbxt_assert(sel->vertices.count == 0);
		ufbxt_assert(sel->edges.count == 4);
		ufbxt_assert(sel->faces.count == 0);

		for (size_t i = 0; i < sel->edges.count; i++) {
			ufbx_edge edge = mesh->edges[sel->edges.data[i]];
			for (size_t j = 0; j < 2; j++) {
				ufbx_vec3 pos = ufbx_get_vertex_vec3(&mesh->vertex_position, edge.indices[j]);
				pos = ufbx_transform_position(&node->geometry_to_world, pos);
				ufbxt_assert_close_real(err, pos.y / 10.0f, 2.0f);
			}
		}
	}

	{
		ufbx_selection_set *set = (ufbx_selection_set*)ufbx_find_element(scene, UFBX_ELEMENT_SELECTION_SET, "Box001_BottomEdges_Edge");
		ufbxt_assert(set && set->nodes.count == 1);
		ufbx_selection_node *sel = set->nodes.data[0];
		ufbxt_assert(sel->target_node == node && sel->target_mesh == mesh);
		ufbxt_assert(!sel->include_node);
		ufbxt_assert(sel->vertices.count == 0);
		ufbxt_assert(sel->edges.count == 4);
		ufbxt_assert(sel->faces.count == 0);

		ufbx_mesh *mesh = sel->target_mesh;
		for (size_t i = 0; i < sel->edges.count; i++) {
			ufbx_edge edge = mesh->edges[sel->edges.data[i]];
			for (size_t j = 0; j < 2; j++) {
				ufbx_vec3 pos = ufbx_get_vertex_vec3(&mesh->vertex_position, edge.indices[j]);
				pos = ufbx_transform_position(&node->geometry_to_world, pos);
				ufbxt_assert_close_real(err, pos.y / 10.0f, 0.0f);
			}
		}
	}

	{
		ufbx_selection_set *set = (ufbx_selection_set*)ufbx_find_element(scene, UFBX_ELEMENT_SELECTION_SET, "Box001_TopVerts_Vertex");
		ufbxt_assert(set && set->nodes.count == 1);
		ufbx_selection_node *sel = set->nodes.data[0];
		ufbxt_assert(sel->target_node == node && sel->target_mesh == mesh);
		ufbxt_assert(!sel->include_node);
		ufbxt_assert(sel->vertices.count == 4);
		ufbxt_assert(sel->edges.count == 0);
		ufbxt_assert(sel->faces.count == 0);

		for (size_t i = 0; i < sel->vertices.count; i++) {
			ufbx_vec3 pos = mesh->vertices[sel->vertices.data[i]];
			pos = ufbx_transform_position(&sel->target_node->geometry_to_world, pos);
			ufbxt_assert_close_real(err, pos.y / 10.0f, 2.0f);
		}
	}

	{
		ufbx_selection_set *set = (ufbx_selection_set*)ufbx_find_element(scene, UFBX_ELEMENT_SELECTION_SET, "Box001_BottomVerts_Vertex");
		ufbxt_assert(set && set->nodes.count == 1);
		ufbx_selection_node *sel = set->nodes.data[0];
		ufbxt_assert(sel->target_node == node && sel->target_mesh == mesh);
		ufbxt_assert(!sel->include_node);
		ufbxt_assert(sel->vertices.count == 4);
		ufbxt_assert(sel->edges.count == 0);
		ufbxt_assert(sel->faces.count == 0);

		for (size_t i = 0; i < sel->vertices.count; i++) {
			ufbx_vec3 pos = mesh->vertices[sel->vertices.data[i]];
			pos = ufbx_transform_position(&sel->target_node->geometry_to_world, pos);
			ufbxt_assert_close_real(err, pos.y / 10.0f, 0.0f);
		}
	}
}
#endif
