#include "ratpoison.h"
#include <stdlib.h>
#include <assert.h>
#include <regex.h>

typedef struct rp_screen_matcher rp_screen_matcher;
struct rp_screen_matcher
{
  struct list_head node;
  int screen;
  regex_t regex;
};

void
rp_screen_matchers_init(struct rp_screen_matchers * matchers)
{
  assert(matchers);
  INIT_LIST_HEAD(&matchers->matchers);
}

void
rp_screen_matchers_free(struct rp_screen_matchers * matchers) {
  rp_screen_matcher * matcher;
  if (matchers) {
    list_for_each_entry (matcher, &matchers->matchers, node) {
      regfree(&matcher->regex);
      free(matcher);
    }
    INIT_LIST_HEAD(&matchers->matchers);
  }
}

rp_screen_matcher *
find_screen_matcher(struct rp_screen_matchers * matchers, int screen) {
  assert(matchers);
  rp_screen_matcher * matcher;

  list_for_each_entry (matcher, &matchers->matchers, node) {
    if (matcher->screen == screen) {
      return matcher;
    }
  }

  return NULL;
}

int
rp_screen_matchers_set_regex(struct rp_screen_matchers * matchers,
                             int screen,
                             const char * fmt) {
  assert(matchers);
  int reti;
  rp_screen_matcher * matcher;

  // search if we already have one registered and remove it;
  matcher = find_screen_matcher(matchers, screen);
  if (matcher) {
    list_del(&matcher->node);
    regfree(&matcher->regex);
    free(matcher);
  }

  if (fmt == NULL || strcmp("", fmt) == 0) {
    return 0; // do not insert an entry if there is no regex
  }

  matcher = (rp_screen_matcher*) malloc(sizeof(rp_screen_matcher));
  matcher->screen = screen;

  // compile the regex
  reti = regcomp(&matcher->regex, fmt, REG_EXTENDED);
  if (reti) {
    free(matcher);
    return reti;
  }
  list_add_tail(&matcher->node, &matchers->matchers);
  return 0;
}

int
rp_screen_matchers_find_screen(struct rp_screen_matchers * matchers,
                               const char * str) {
  assert(matchers);
  rp_screen_matcher * matcher;
  int reti;

  if (str == NULL) {
    return -1;
  }

  list_for_each_entry (matcher, &matchers->matchers, node) {
    reti = regexec(&matcher->regex, str, 0, NULL, 0);
    if (!reti) {
      // we have a match
      return matcher->screen;
    }
  }

  return -1;
}
