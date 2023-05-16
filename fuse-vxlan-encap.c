#include <rte_flow.h>

#define VOLUMES_NUM 4

static struct rte_flow_item vxlan_encap_template_patterns[VOLUMES_NUM][8] = {
	{
		{.type = RTE_FLOW_ITEM_TYPE_ETH},
		{.type = RTE_FLOW_ITEM_TYPE_IPV4},
		{.type = RTE_FLOW_ITEM_TYPE_UDP},
		{.type = RTE_FLOW_ITEM_TYPE_VXLAN},
		{.type = RTE_FLOW_ITEM_TYPE_END},
	},
	{
		{.type = RTE_FLOW_ITEM_TYPE_ETH},
		{.type = RTE_FLOW_ITEM_TYPE_VLAN},
		{.type = RTE_FLOW_ITEM_TYPE_IPV4},
		{.type = RTE_FLOW_ITEM_TYPE_UDP},
		{.type = RTE_FLOW_ITEM_TYPE_VXLAN},
		{.type = RTE_FLOW_ITEM_TYPE_END},
	},
	{
		{.type = RTE_FLOW_ITEM_TYPE_ETH},
		{.type = RTE_FLOW_ITEM_TYPE_IPV6},
		{.type = RTE_FLOW_ITEM_TYPE_UDP},
		{.type = RTE_FLOW_ITEM_TYPE_VXLAN},
		{.type = RTE_FLOW_ITEM_TYPE_END},
	},
	{
		{.type = RTE_FLOW_ITEM_TYPE_ETH},
		{.type = RTE_FLOW_ITEM_TYPE_VLAN},
		{.type = RTE_FLOW_ITEM_TYPE_IPV6},
		{.type = RTE_FLOW_ITEM_TYPE_UDP},
		{.type = RTE_FLOW_ITEM_TYPE_VXLAN},
		{.type = RTE_FLOW_ITEM_TYPE_END},
	},
};

static struct rte_flow_action_vxlan_encap vxlan_encap = {
		.definition = NULL
};

static struct rte_flow_action template_encap_actions[VOLUMES_NUM][4] = {
	{
		{
			.type = RTE_FLOW_ACTION_TYPE_VXLAN_ENCAP,
			.conf = &(struct rte_flow_action_vxlan_encap) {
				.definition = vxlan_encap_template_patterns[0]
			}
		},
		{.type = RTE_FLOW_ACTION_TYPE_JUMP},
		{.type = RTE_FLOW_ACTION_TYPE_END}
	},
	{
		{
			.type = RTE_FLOW_ACTION_TYPE_VXLAN_ENCAP,
			.conf = &(struct rte_flow_action_vxlan_encap) {
				.definition = vxlan_encap_template_patterns[1]
			}
		},
		{.type = RTE_FLOW_ACTION_TYPE_JUMP},
		{.type = RTE_FLOW_ACTION_TYPE_END}
	},
	{
		{
			.type = RTE_FLOW_ACTION_TYPE_VXLAN_ENCAP,
			.conf = &(struct rte_flow_action_vxlan_encap) {
				.definition = vxlan_encap_template_patterns[2]
			}
		},
		{.type = RTE_FLOW_ACTION_TYPE_JUMP},
		{.type = RTE_FLOW_ACTION_TYPE_END}
	},
	{
		{
			.type = RTE_FLOW_ACTION_TYPE_VXLAN_ENCAP,
			.conf = &(struct rte_flow_action_vxlan_encap) {
				.definition = vxlan_encap_template_patterns[3]
			}
		},
		{.type = RTE_FLOW_ACTION_TYPE_JUMP},
		{.type = RTE_FLOW_ACTION_TYPE_END}
	},
};

static struct rte_flow_action masks[] = {
	{.type = RTE_FLOW_ACTION_TYPE_VXLAN_ENCAP},
	{.type = RTE_FLOW_ACTION_TYPE_JUMP},
	{.type = RTE_FLOW_ACTION_TYPE_END}
};

struct actions_template_fuse_volume {
	struct rte_flow_actions_template_attr *attr;
	struct rte_flow_action *actions, *masks;
} volumes_actions_templates[VOLUMES_NUM] = {
	{.actions = template_encap_actions[0], .masks = masks},
	{.actions = template_encap_actions[1], .masks = masks},
	{.actions = template_encap_actions[2], .masks = masks},
	{.actions = template_encap_actions[3], .masks = masks},
};


