#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>

int columns = 80, width = 80, padding = 0, indentation = 0;
#define arrsize(x) (sizeof(x)/sizeof(x[0]))

void dotitle(int level, const char *title) {
  // todo: use wchar_t?
  struct {
    char topleft[4],
         topright[4],
         bottomleft[4],
         bottomright[4],
         horiz[4],
         vert[4];
  } chars[] = {
    { "┏", "┓", "┗", "┛", "━", "┃" },
    { "╔", "╗", "╚", "╝", "═", "║" },
    { "┌", "┐", "└", "┘", "─", "│" },
    { "+", "+", "+", "+", "-", "|" },
  };

  if (level > arrsize(chars) - 1) level = arrsize(chars) - 1;

  int len = strlen(title) + 2;

  printf("%*s%s", padding + indentation, "", chars[level].topleft);
  for (int i = 0; i < len; i++) printf("%s", chars[level].horiz);
  printf("%s\n", chars[level].topright);

  printf("%*s%s %s %s\n", padding + indentation, "", chars[level].vert, title, chars[level].vert);

  printf("%*s%s", padding + indentation, "", chars[level].bottomleft);
  for (int i = 0; i < len; i++) printf("%s", chars[level].horiz);
  printf("%s\n\n", chars[level].bottomright);
}

void dohr() {
  printf("%*s", padding + indentation, "");
  for (int i = 0; i < width; i++)
    printf("%s", "─");
  printf("\n\n");
}

// todo:
// - utf8
// - justification
void doparagraph(const char *paragraph) {
  char *par = strdup(paragraph);
  char *tok = strtok(par, " \t");
  if (tok) printf("%*s", padding, "");
  int col = 0;
  while (tok) {
    int len = strlen(tok) + 1;
    if ((col += len) > width) {
      printf("\n%*s", padding, "");
      col = len;
    }
    printf("%s ", tok);
    tok = strtok(NULL, " \t");
  }
  if (col) printf("\n");
  printf("\n");
}
void docodeblock(const char *lang, const char *code) {
}

void docitation(const char *citation) {
}

int main(int argc, char *argv[]) {
  {
    struct winsize ws;
    char *str = getenv("COLUMNS");
    if (str) columns = atoi(str);
    else if (!ioctl(1, TIOCGWINSZ, &ws)) columns = ws.ws_col;
  }
  if (columns > 80) {
    if ((columns * 3 / 4) > 80) width = columns * 3 / 4;
    padding = (columns - width) / 2;
  }

  dotitle(0, "heading 1 asdfaslidkfjasf");
  dotitle(1, "heading 2 asdfasdjfajsdf");
  dotitle(2, "heading 3 aslkjdfkasdlfasldfalfl");
  dotitle(3, "heading 4 askdflaslklklllllkl");
  const char *lipsum[] = {
"\
Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed vitae nunc\
viverra, scelerisque ipsum eu, consequat dolor. Sed dapibus maximus accumsan.\
Sed sed porta tortor, non scelerisque eros. Donec fermentum mauris nulla, non\
fringilla est feugiat quis. Proin leo massa, venenatis vitae est ac, molestie\
aliquam arcu. Phasellus euismod aliquet posuere. Ut mollis erat sit amet lorem\
feugiat luctus. Aenean mauris diam, accumsan rhoncus nulla sed, molestie mattis\
velit. Nullam condimentum euismod aliquet. Vivamus eu accumsan ante. In rhoncus\
eget nunc vel dictum. Pellentesque id porttitor dui. Phasellus dolor mauris,\
rhoncus cursus risus non, pharetra tristique magna. Phasellus facilisis blandit\
varius. Fusce est purus, auctor sed mattis non, rutrum et leo. In eu lectus eu\
nisl maximus facilisis id a ex.\
",
"\
Quisque ut justo vel lacus pulvinar semper nec quis ex. Nulla facilisi.\
Suspendisse facilisis nec lorem eu cursus. Donec massa ipsum, aliquam vitae\
auctor lacinia, condimentum eu lectus. Vestibulum eleifend ligula a ipsum\
aliquet, non viverra metus viverra. Nunc nec massa mattis neque vehicula\
ultricies sit amet a libero. Sed sit amet pulvinar mauris. Nunc pellentesque\
felis a purus consequat, at rutrum dui viverra.\
",
"\
Nulla porta eros vel dui venenatis mattis. Praesent malesuada, nunc at commodo\
tincidunt, mi odio vehicula orci, vel venenatis nulla tellus pharetra augue.\
Nullam dapibus diam neque, et eleifend purus placerat in. Praesent at tempor\
felis, quis egestas quam. Nulla sed pulvinar turpis. Praesent gravida nisi in\
lorem iaculis feugiat. Fusce eget eros eu diam congue ornare. Integer eleifend\
pulvinar faucibus. Integer bibendum dignissim tortor, vel pharetra eros\
pulvinar eu. Donec venenatis libero ac bibendum molestie. Maecenas blandit\
fringilla ex sed maximus. Quisque posuere in ligula ornare mollis.\
",
"\
Proin interdum metus ac lectus semper bibendum. Curabitur elementum, mauris eu\
sodales rhoncus, ipsum dui venenatis metus, convallis mattis nunc tellus sed\
dui. Nulla hendrerit mi elit, in porttitor lacus semper et. Vestibulum vel\
imperdiet arcu. Donec pulvinar lectus velit, eget sagittis odio tincidunt eu.\
Sed vehicula scelerisque purus, nec laoreet diam ultricies ut. Donec maximus mi\
sed turpis efficitur, nec gravida risus porta. Maecenas quis risus hendrerit\
odio dapibus pulvinar eget vitae enim. Nulla feugiat mauris et viverra auctor.\
Duis aliquam purus fermentum nibh mattis, non faucibus justo malesuada.\
",
"\
Mauris hendrerit, lectus ut maximus facilisis, mauris tellus blandit felis, at\
aliquet augue elit egestas sem. Curabitur sit amet est eget ipsum vehicula\
ultricies. Suspendisse viverra risus magna, a interdum nulla porta sed.\
Pellentesque sollicitudin pharetra suscipit. Suspendisse nec feugiat est, ac\
eleifend ante. Mauris sed elit tristique, sagittis nisl et, condimentum leo.\
Vivamus iaculis nisl egestas, sodales turpis eleifend, consequat ante.\
Curabitur varius lacinia ex eu iaculis. Quisque in eros ac magna maximus\
euismod. Sed a nisi congue orci molestie tincidunt. Etiam fermentum risus at\
eleifend fermentum. Vestibulum vestibulum tincidunt nunc, eget accumsan enim\
posuere consequat. Quisque fermentum libero ligula, sit amet dictum ex cursus\
ac. Pellentesque habitant morbi tristique senectus et netus et malesuada fames\
ac turpis egestas. Proin ut finibus tortor.\
"
  };
  for (int i = 0; i < 4; i++) doparagraph(lipsum[i]);
  dohr();
  doparagraph(lipsum[4]);
  docodeblock("", "this is code\nstill code\neven moar code\nso much code");
  docitation("Don't believe everything you read on the internet\n\n-- Abraham Lincoln");
  return 0;
}
