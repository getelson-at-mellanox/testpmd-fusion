#include <rte_flow.h>
#include <rte_testpmd_fusion.h>

static struct rte_flow_action_modify_field modify_ipv4_src_conf = {
	.operation = RTE_FLOW_MODIFY_SET,
	.dst = { .field = RTE_FLOW_FIELD_IPV4_SRC },
	.src = { 
		.field = RTE_FLOW_FIELD_VALUE,
		.level = RTE_BE32(0x12131415)
	},
	.width = 32
};

static struct rte_flow_action_modify_field modify_ipv4_dst_conf = {
	.operation = RTE_FLOW_MODIFY_SET,
	.dst = { .field = RTE_FLOW_FIELD_IPV4_DST },
	.src = { 
		.field = RTE_FLOW_FIELD_VALUE,
		.level = RTE_BE32(0x21222324)
	},
	.width = 32
};


static struct rte_flow_action modify_field_empty_mask = {
	.type = RTE_FLOW_ACTION_TYPE_MODIFY_FIELD
};

static struct rte_flow_action unit_1_spec[] = {
	{ .type = RTE_FLOW_ACTION_TYPE_MODIFY_FIELD, .conf = &modify_ipv4_src_conf},
	{ .type = RTE_FLOW_ACTION_TYPE_JUMP},
	{ .type = RTE_FLOW_ACTION_TYPE_END}
};

static struct rte_flow_action unit_2_spec[] = {
	{ .type = RTE_FLOW_ACTION_TYPE_MODIFY_FIELD, .conf = &modify_ipv4_dst_conf},
	{ .type = RTE_FLOW_ACTION_TYPE_JUMP},
	{ .type = RTE_FLOW_ACTION_TYPE_END}
};

static struct rte_flow_action unit_3_spec[] = {
	{ .type = RTE_FLOW_ACTION_TYPE_MODIFY_FIELD, .conf = &modify_ipv4_src_conf},
	{ .type = RTE_FLOW_ACTION_TYPE_MODIFY_FIELD, .conf = &modify_ipv4_dst_conf},
	{ .type = RTE_FLOW_ACTION_TYPE_JUMP},
	{ .type = RTE_FLOW_ACTION_TYPE_END}
};

static struct rte_flow_action unit_1_mask[] = {
	{ .type = RTE_FLOW_ACTION_TYPE_MODIFY_FIELD},
	{ .type = RTE_FLOW_ACTION_TYPE_JUMP},
	{ .type = RTE_FLOW_ACTION_TYPE_END}
};

static struct rte_flow_action unit_3_mask[] = {
	{ .type = RTE_FLOW_ACTION_TYPE_MODIFY_FIELD},
	{ .type = RTE_FLOW_ACTION_TYPE_MODIFY_FIELD},
	{ .type = RTE_FLOW_ACTION_TYPE_JUMP},
	{ .type = RTE_FLOW_ACTION_TYPE_END}
};

struct fuse_unit_actions_template actions_templates_units[] = {
	[0] = { 
		.actions = unit_1_spec, 
		.masks = unit_1_mask,
		.actions_aid = "modify_field op set dst_type ipv4_src src_type value src_value 0x12131415 width 32 / jump / end",
		.masks_aid = "modify_field / jump / end"
	},
	[1] = { 
		.actions = unit_2_spec, 
		.masks = unit_1_mask,
		.actions_aid = "modify_field op set dst_type ipv4_dst src_type value src_value 0x21222324 width 32 / jump / end",
		.masks_aid = "modify_field / jump / end"
	},
	[2] = {
		.actions = unit_3_spec, 
		.masks = unit_3_mask,
		.actions_aid = "modify_field op set dst_type ipv4_src src_type value src_value 0x12131415 width 32 / modify_field op set dst_type ipv4_dst src_type value src_value 0x21222324 width 32 / jump / end",
		.masks_aid = "modify_field / modify_field / jump / end"
	}
};