#include <rte_flow.h>

/**
 * @brief 
 * set raw_encap 1 eth src is 11:22:33:44:55:66 dst is aa:bb:cc:dd:01:aa / ipv4 src is 31.31.31.31 dst is 63.63.63.1 / udp src is 1 / vxlan vni is 1 / end_set
 * # total data size is 50
 * set raw_encap 2 eth src is 11:22:33:44:55:66 dst is aa:bb:cc:dd:02:aa / vlan vid is 2 / ipv4 src is 31.31.31.31 dst is 63.63.63.2 / udp src is 2 / vxlan vni is 2 / end_set
 * # total data size is 54
 * set raw_encap 3 eth src is 11:22:33:44:55:66 dst is aa:bb:cc:dd:03:aa / ipv6 src is fc00::31 dst is fc00::3 / udp src is 3 / vxlan vni is 3 / end_set
 * # total data size is 70
 * set raw_encap 4 eth src is 11:22:33:44:55:66 dst is aa:bb:cc:dd:04:aa / vlan vid is 4 / ipv6 src is fc00::31 dst is fc00::4 / udp src is 4 / vxlan vni is 4 / end_set
 * # total data size is 74
 */
#define VOLUMES_NUM 4

static struct rte_flow_action template_vxlan_encap_actions[VOLUMES_NUM][4] = {
	{
		{
			.type = RTE_FLOW_ACTION_TYPE_RAW_ENCAP,
			.conf = &(struct rte_flow_action_raw_encap) { .size = 50 }
		},
		{.type = RTE_FLOW_ACTION_TYPE_JUMP},
		{.type = RTE_FLOW_ACTION_TYPE_END}
	},
	{
		{
			.type = RTE_FLOW_ACTION_TYPE_RAW_ENCAP,
			.conf = &(struct rte_flow_action_raw_encap) { .size = 54 }
		},
		{.type = RTE_FLOW_ACTION_TYPE_JUMP},
		{.type = RTE_FLOW_ACTION_TYPE_END}
	},
	{
		{
			.type = RTE_FLOW_ACTION_TYPE_RAW_ENCAP,
			.conf = &(struct rte_flow_action_raw_encap) { .size = 70 }
		},
		{.type = RTE_FLOW_ACTION_TYPE_JUMP},
		{.type = RTE_FLOW_ACTION_TYPE_END}
	},
	{
		{
			.type = RTE_FLOW_ACTION_TYPE_RAW_ENCAP,
			.conf = &(struct rte_flow_action_raw_encap) { .size = 74 }
		},
		{.type = RTE_FLOW_ACTION_TYPE_JUMP},
		{.type = RTE_FLOW_ACTION_TYPE_END}
	},
};

static struct rte_flow_action masks[] = {
	{.type = RTE_FLOW_ACTION_TYPE_RAW_ENCAP, .conf = &(struct rte_flow_action_raw_encap) { .size = 0xffffffff } },
	{.type = RTE_FLOW_ACTION_TYPE_JUMP},
	{.type = RTE_FLOW_ACTION_TYPE_END}
};

struct actions_template_fuse_volume {
	struct rte_flow_actions_template_attr *attr;
	struct rte_flow_action *actions, *masks;
} volumes_actions_templates[VOLUMES_NUM] = {
	{.actions = template_vxlan_encap_actions[0], .masks = masks},
	{.actions = template_vxlan_encap_actions[1], .masks = masks},
	{.actions = template_vxlan_encap_actions[2], .masks = masks},
	{.actions = template_vxlan_encap_actions[3], .masks = masks},
};
