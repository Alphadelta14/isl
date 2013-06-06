#ifndef ISL_AST_H
#define ISL_AST_H

#include <isl/ctx.h>
#include <isl/id.h>
#include <isl/val.h>
#include <isl/list.h>
#include <isl/printer.h>

#if defined(__cplusplus)
extern "C" {
#endif

struct isl_ast_expr;
typedef struct isl_ast_expr isl_ast_expr;

struct isl_ast_node;
typedef struct isl_ast_node isl_ast_node;

enum isl_ast_op_type {
	isl_ast_op_error = -1,
	isl_ast_op_and,
	isl_ast_op_and_then,
	isl_ast_op_or,
	isl_ast_op_or_else,
	isl_ast_op_max,
	isl_ast_op_min,
	isl_ast_op_minus,
	isl_ast_op_add,
	isl_ast_op_sub,
	isl_ast_op_mul,
	isl_ast_op_div,
	isl_ast_op_fdiv_q,	/* Round towards -infty */
	isl_ast_op_pdiv_q,	/* Dividend is non-negative */
	isl_ast_op_pdiv_r,	/* Dividend is non-negative */
	isl_ast_op_cond,
	isl_ast_op_select,
	isl_ast_op_eq,
	isl_ast_op_le,
	isl_ast_op_lt,
	isl_ast_op_ge,
	isl_ast_op_gt,
	isl_ast_op_call,
	isl_ast_op_access
};

enum isl_ast_expr_type {
	isl_ast_expr_error = -1,
	isl_ast_expr_op,
	isl_ast_expr_id,
	isl_ast_expr_int
};

enum isl_ast_node_type {
	isl_ast_node_error = -1,
	isl_ast_node_for = 1,
	isl_ast_node_if,
	isl_ast_node_block,
	isl_ast_node_user
};

struct isl_ast_print_options;
typedef struct isl_ast_print_options isl_ast_print_options;

ISL_DECLARE_LIST(ast_expr)
ISL_DECLARE_LIST(ast_node)

int isl_options_set_ast_iterator_type(isl_ctx *ctx, const char *val);
const char *isl_options_get_ast_iterator_type(isl_ctx *ctx);

__isl_give isl_ast_expr *isl_ast_expr_from_val(__isl_take isl_val *v);
__isl_give isl_ast_expr *isl_ast_expr_from_id(__isl_take isl_id *id);
__isl_give isl_ast_expr *isl_ast_expr_neg(__isl_take isl_ast_expr *expr);
__isl_give isl_ast_expr *isl_ast_expr_add(__isl_take isl_ast_expr *expr1,
	__isl_take isl_ast_expr *expr2);
__isl_give isl_ast_expr *isl_ast_expr_sub(__isl_take isl_ast_expr *expr1,
	__isl_take isl_ast_expr *expr2);
__isl_give isl_ast_expr *isl_ast_expr_mul(__isl_take isl_ast_expr *expr1,
	__isl_take isl_ast_expr *expr2);
__isl_give isl_ast_expr *isl_ast_expr_div(__isl_take isl_ast_expr *expr1,
	__isl_take isl_ast_expr *expr2);
__isl_give isl_ast_expr *isl_ast_expr_and(__isl_take isl_ast_expr *expr1,
	__isl_take isl_ast_expr *expr2);
__isl_give isl_ast_expr *isl_ast_expr_or(__isl_take isl_ast_expr *expr1,
	__isl_take isl_ast_expr *expr2);
__isl_give isl_ast_expr *isl_ast_expr_access(__isl_take isl_ast_expr *array,
	__isl_take isl_ast_expr_list *indices);

__isl_give isl_ast_expr *isl_ast_expr_copy(__isl_keep isl_ast_expr *expr);
void *isl_ast_expr_free(__isl_take isl_ast_expr *expr);

isl_ctx *isl_ast_expr_get_ctx(__isl_keep isl_ast_expr *expr);
enum isl_ast_expr_type isl_ast_expr_get_type(__isl_keep isl_ast_expr *expr);
__isl_give isl_val *isl_ast_expr_get_val(__isl_keep isl_ast_expr *expr);
__isl_give isl_id *isl_ast_expr_get_id(__isl_keep isl_ast_expr *expr);

enum isl_ast_op_type isl_ast_expr_get_op_type(__isl_keep isl_ast_expr *expr);
int isl_ast_expr_get_op_n_arg(__isl_keep isl_ast_expr *expr);
__isl_give isl_ast_expr *isl_ast_expr_get_op_arg(__isl_keep isl_ast_expr *expr,
	int pos);

int isl_ast_expr_is_equal(__isl_keep isl_ast_expr *expr1,
	__isl_keep isl_ast_expr *expr2);

__isl_give isl_printer *isl_printer_print_ast_expr(__isl_take isl_printer *p,
	__isl_keep isl_ast_expr *expr);
void isl_ast_expr_dump(__isl_keep isl_ast_expr *expr);
__isl_give char *isl_ast_expr_to_str(__isl_keep isl_ast_expr *expr);

__isl_give isl_ast_node *isl_ast_node_alloc_user(__isl_take isl_ast_expr *expr);
__isl_give isl_ast_node *isl_ast_node_copy(__isl_keep isl_ast_node *node);
void *isl_ast_node_free(__isl_take isl_ast_node *node);

isl_ctx *isl_ast_node_get_ctx(__isl_keep isl_ast_node *node);
enum isl_ast_node_type isl_ast_node_get_type(__isl_keep isl_ast_node *node);

__isl_give isl_ast_node *isl_ast_node_set_annotation(
	__isl_take isl_ast_node *node, __isl_take isl_id *annotation);
__isl_give isl_id *isl_ast_node_get_annotation(__isl_keep isl_ast_node *node);

__isl_give isl_ast_expr *isl_ast_node_for_get_iterator(
	__isl_keep isl_ast_node *node);
__isl_give isl_ast_expr *isl_ast_node_for_get_init(
	__isl_keep isl_ast_node *node);
__isl_give isl_ast_expr *isl_ast_node_for_get_cond(
	__isl_keep isl_ast_node *node);
__isl_give isl_ast_expr *isl_ast_node_for_get_inc(
	__isl_keep isl_ast_node *node);
__isl_give isl_ast_node *isl_ast_node_for_get_body(
	__isl_keep isl_ast_node *node);
int isl_ast_node_for_is_degenerate(__isl_keep isl_ast_node *node);

__isl_give isl_ast_expr *isl_ast_node_if_get_cond(
	__isl_keep isl_ast_node *node);
__isl_give isl_ast_node *isl_ast_node_if_get_then(
	__isl_keep isl_ast_node *node);
int isl_ast_node_if_has_else(__isl_keep isl_ast_node *node);
__isl_give isl_ast_node *isl_ast_node_if_get_else(
	__isl_keep isl_ast_node *node);

__isl_give isl_ast_node_list *isl_ast_node_block_get_children(
	__isl_keep isl_ast_node *node);

__isl_give isl_ast_expr *isl_ast_node_user_get_expr(
	__isl_keep isl_ast_node *node);

__isl_give isl_printer *isl_printer_print_ast_node(__isl_take isl_printer *p,
	__isl_keep isl_ast_node *node);
void isl_ast_node_dump(__isl_keep isl_ast_node *node);

__isl_give isl_ast_print_options *isl_ast_print_options_alloc(isl_ctx *ctx);
__isl_give isl_ast_print_options *isl_ast_print_options_copy(
	__isl_keep isl_ast_print_options *options);
void *isl_ast_print_options_free(__isl_take isl_ast_print_options *options);
isl_ctx *isl_ast_print_options_get_ctx(
	__isl_keep isl_ast_print_options *options);

__isl_give isl_ast_print_options *isl_ast_print_options_set_print_user(
	__isl_take isl_ast_print_options *options,
	__isl_give isl_printer *(*print_user)(__isl_take isl_printer *p,
		__isl_take isl_ast_print_options *options,
		__isl_keep isl_ast_node *node, void *user),
	void *user);
__isl_give isl_ast_print_options *isl_ast_print_options_set_print_for(
	__isl_take isl_ast_print_options *options,
	__isl_give isl_printer *(*print_for)(__isl_take isl_printer *p,
		__isl_take isl_ast_print_options *options,
		__isl_keep isl_ast_node *node, void *user),
	void *user);

int isl_ast_node_foreach_ast_op_type(__isl_keep isl_ast_node *node,
	int (*fn)(enum isl_ast_op_type type, void *user), void *user);
__isl_give isl_printer *isl_ast_op_type_print_macro(
	enum isl_ast_op_type type, __isl_take isl_printer *p);
__isl_give isl_printer *isl_ast_node_print_macros(
	__isl_keep isl_ast_node *node, __isl_take isl_printer *p);
__isl_give isl_printer *isl_ast_node_print(__isl_keep isl_ast_node *node,
	__isl_take isl_printer *p,
	__isl_take isl_ast_print_options *options);
__isl_give isl_printer *isl_ast_node_for_print(__isl_keep isl_ast_node *node,
	__isl_take isl_printer *p,
	__isl_take isl_ast_print_options *options);
__isl_give isl_printer *isl_ast_node_if_print(__isl_keep isl_ast_node *node,
	__isl_take isl_printer *p,
	__isl_take isl_ast_print_options *options);

#if defined(__cplusplus)
}
#endif

#endif
