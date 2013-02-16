#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "poly.h"

#define T poly_t

typedef struct node_t *link;

struct node_t {
    coeff_t coeff;
    exp_t  exp;
    link   next;
};

struct T {
    link head;
};

static void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

static link newlink(coeff_t coeff, exp_t exp, link next)
{
    link l  = alloc(sizeof * l);
    l->coeff = coeff;
    l->exp  = exp;
    l->next = next;
    return l;
}

static void dellink(link *l)
{
    free(*l);
    *l = NULL;
}

T poly_init(coeff_t coeff, exp_t exp)
{
    T t     = alloc(sizeof * t);
    link l  = newlink(coeff, exp, NULL);
    t->head = l;
    return t;
}

void poly_finalize(T *t)
{
    link tmp;

    while ((tmp = (*t)->head) != NULL) {
        (*t)->head = tmp->next;
        dellink(&tmp);
    }

    free(*t);
    *t = NULL;
}

T poly_add(T adder1, T adder2)
{
    link sumcur;
    link adder1cur = adder1->head;
    link adder2cur = adder2->head;;
    T sum;
    coeff_t c;
    exp_t e;
    sum       = alloc(sizeof * sum);
    sumcur = sum->head = NULL;

    while (adder1cur != NULL && adder2cur != NULL) {
        if (adder1->head->exp > adder2->head->exp) {
            c         = adder1->head->coeff;
            e         = adder1->head->exp;
            adder1cur = adder1cur->next;
        } else if (adder1->head->exp == adder2->head->exp) {
            c = adder1->head->coeff + adder2->head->coeff;
            e = adder1->head->exp;
            adder1cur = adder1cur->next;
            adder1cur = adder1cur->next;
        } else {
            c         = adder2->head->coeff;
            e         = adder2->head->exp;
            adder2cur = adder2cur->next;
        }

        if (sum->head == NULL) {
            sum->head = newlink(c, e, NULL);
        } else {
            sumcur->next = newlink(c, e, NULL);
            sumcur       = sumcur->next;
        }
    }

    while (adder1cur != NULL) {
        sumcur->next = newlink(adder1cur->coeff, adder1cur->exp, NULL);
        sumcur       = sumcur->next;
        adder1cur    = adder1cur->next;
    }

    while (adder2cur != NULL) {
        sumcur->next = newlink(adder2cur->coeff, adder2cur->exp, NULL);
        sumcur       = sumcur->next;
        adder2cur    = adder2cur->next;
    }

    return sum;
}

