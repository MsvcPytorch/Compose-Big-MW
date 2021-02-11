#include <graphics.h>
#include <ege/fps.h>
#include <cmath>
#include <time.h>
#include <cstdio>
#include <cstdlib>
#define myrand(m)                 ((float)random(10000) * m / 10000.0f)
#define IsCrash(a, b)             ((a.x - b.x)*(a.x - b.x)+(a.y - b.y)*(a.y - b.y) < (a.r + b.r)*(a.r + b.r))
#define IsWEdge(a)               (a.x < a.r || a.x >= 1440-a.r)
#define IsHEdge(a)               (a.y < a.r || a.y >= 960-a.r)
#define IsEdge(a)                 (IsWEdge(a) || IsHEdge(a))
#define Distance(x1, y1, x2, y2) (((x1) - (x2))*((x1) - (x2)) + ((y1) - (y2))*((y1) - (y2)))
using namespace std;
int num = 5;
mouse_msg msg = { 0 };
typedef struct {
    float x, y;
    float vx, vy;
    int r;
    int color;
    int level;
} Obj;


//瀹氫箟涓€涓狝niObj绫?
class AniObj {
public:
    AniObj() {
        n = 5;
        int i, j;
        int rd;
        bool goon;
        for (i = 0; i < n; i++) {
            do {
                rd = rand() % 3 + 1;
                goon = false;
                obj[i].x = (float)random(getwidth());
                obj[i].y = (float)random(getheight());
                obj[i].r = rd * 10 + 20;
                obj[i].level = rd;
                if (IsEdge(obj[i]))
                    goon = true;
                else if (i != 0)
                    for (j = i - 1; j >= 0; j--)
                        if (IsCrash(obj[i], obj[j])) {
                            goon = true;
                            break;
                        }
            } while (goon);
            obj[i].vx = obj[i].vy = 0.0f;
            obj[i].color = EGEAGRAY(0xff, HSVtoRGB(myrand(360.0f), 1.0f, 1.0f));
        }
    }
    void addnewele()
    {//printf("%d %d",msg.x,msg.y);
        obj[num].x = msg.x;
        obj[num].y = msg.y;
        obj[num].vx = obj[num + 1].vy = 0.0f;
        obj[num].color = EGEAGRAY(0xff, HSVtoRGB(myrand(360.0f), 1.0f, 1.0f));
        obj[num].r = 30;
        obj[num].level = 1;
        for (int y = 1; y <= num - 1; y++)
        {
            if (IsCrash(obj[num], obj[y]))
            {
                printf("不要重叠放置！\n");
                return;
            }
        }
        n++;
        num++;
    }

    void fly()
    {
        for (int i = 0; i < n; i++)
        {
            obj[i].vy = -7;
            obj[i].vx = rand() % 11 - 6;
        }
    }
    //鏇存柊浣嶇疆绛夌浉鍏冲睘鎬?
    void updateobj() {
        int i, j;
        for (i = 0; i < n; i++) {
            if (obj[i].x > 10000)
            {
                obj[i].x = 999999; obj[i].y = 999999; goto b;
            }
            for (int g = 0; g <= num; g++)
            {
                if (IsCrash(obj[i], obj[g]) && obj[g].y < obj[i].y)
                {//obj[i].vy=0;
                    goto a;
                }
            }
            obj[i].vy += 0.05f;
        a:obj[i].x += obj[i].vx;
            obj[i].y += obj[i].vy;
            if (obj[i].y >= 960 - obj[i].r && obj[i].vy > 0) {
                obj[i].y -= obj[i].vy;
                obj[i].vy = -obj[i].vy / 2;
            }
            //if( obj[i].y < obj[i].r  && obj[i].vy < 0)  obj[i].y -= obj[i].vy;obj[i].vy = - obj[i].vy/2;
            if (obj[i].x < obj[i].r && obj[i].vx < 0) obj[i].vx = -obj[i].vx;
            if (obj[i].x >= 1440 - obj[i].r && obj[i].vx > 0) obj[i].vx = -obj[i].vx / 2;
        b:int railgun = 1;
        }

        for (i = 1; i < n; i++)
            for (j = i - 1; j >= 0; j--)
                if (IsCrash(obj[i], obj[j]) &&
                    (Distance(obj[i].x, obj[i].y, obj[j].x, obj[j].y) >
                        Distance(obj[i].x + obj[i].vx, obj[i].y + obj[i].vy, obj[j].x + obj[j].vx, obj[j].y + obj[j].vy)
                        )
                    )
                    Crash(obj[i], obj[j]);
    }

    //鏍规嵁灞炴€у€肩粯鐢?
    void drawobj() {
        for (int i = 0; i < n; i++) {
            if (obj[i].y > 10000)
            {
                goto c;
            }
            setfillcolor(obj[i].color);
            setfont(40, 0, "宋体");
            ege_fillellipse(obj[i].x - obj[i].r, obj[i].y - obj[i].r,
                obj[i].r * 2, obj[i].r * 2);
            switch (obj[i].level) {
            case 1:
            { xyprintf(obj[i].x, obj[i].y, "SZK");
            break;
            }
            case 2:
            {xyprintf(obj[i].x, obj[i].y, "LZM");
            break;
            }
            case 3:
            {xyprintf(obj[i].x, obj[i].y, "ZGD");
            break;
            }
            case 4:
            {xyprintf(obj[i].x, obj[i].y, "WJH");
            break;
            }
            case 5:
            {xyprintf(obj[i].x, obj[i].y, "WJC");
            break;
            }
            case 6:
            {xyprintf(obj[i].x, obj[i].y, "ZX");
            break;
            }
            case 7:
            {xyprintf(obj[i].x, obj[i].y, "ZZQ");
            break;
            }
            case 8:
            {xyprintf(obj[i].x, obj[i].y, "Celery");
            break;
            }
            case 9:
            {xyprintf(obj[i].x, obj[i].y, "Pikaqiu");
            break;
            }
            case 10:
            {xyprintf(obj[i].x, obj[i].y, "Olivia");
            break;
            }
            default:
            {xyprintf(obj[i].x, obj[i].y, "MW"); break;
            }
            }
        c:int railgun = 0;

        }
    }

    ~AniObj() {
    }

private:
    void Crash(Obj& a, Obj& b) {
        float ma = a.r * a.r, mb = b.r * b.r;

        float sx = a.x - b.x;
        float sy = a.y - b.y;
        float s1x = sx / sqrt(sx * sx + sy * sy);
        float s1y = sy / sqrt(sx * sx + sy * sy);
        float t1x = -s1y;
        float t1y = s1x;

        float vas = a.vx * s1x + a.vy * s1y;
        float vat = a.vx * t1x + a.vy * t1y;
        float vbs = b.vx * s1x + b.vy * s1y;
        float vbt = b.vx * t1x + b.vy * t1y;

        float vasf = (2 * mb * vbs + vas * (ma - mb)) / (ma + mb);
        float vbsf = (2 * ma * vas - vbs * (ma - mb)) / (ma + mb);

        float nsx = vasf * s1x;
        float nsy = vasf * s1y;
        float ntx = vat * t1x;
        float nty = vat * t1y;
        //if (a.y>b.y) a.vy=0;return ;


        a.vx = (nsx + ntx) * 2 / 3;
        a.vy = (nsy + nty) * 2 / 3;

        nsx = vbsf * s1x;
        nsy = vbsf * s1y;
        ntx = vbt * t1x;
        nty = vbt * t1y;

        b.vx = (nsx + ntx) * 2 / 3;
        b.vy = (nsy + nty) * 2 / 3;
        if (a.level == b.level)
        {
            b.x = 999999;
            b.y = 999999;
            a.level++;
            a.r = a.r + 10;
        }
    }

private:
    Obj obj[20000];
    int n;
};

int main() {
    srand(time(NULL));
    setinitmode(INIT_ANIMATION);
    initgraph(1440, 960);
    randomize(); //鍒濆鍖栭殢鏈虹瀛?

    AniObj aniobj; //瀹氫箟瀵硅薄
    fps f;
    ege_enable_aa(true);

    for (; is_run(); delay_fps(120)) {
        aniobj.updateobj(); //鏇存柊浣嶇疆
        cleardevice();
        aniobj.drawobj(); //缁樼敾
        for (; is_run(); delay_fps(120)) {
            msg = { 0 };
            aniobj.updateobj();
            while (mousemsg()) {
                msg = getmouse();
                goto a;
            }
            aniobj.updateobj(); //鏇存柊浣嶇疆
            cleardevice();
            aniobj.drawobj();
        }
    a:if (msg.is_left() && msg.is_down())
    {
        aniobj.updateobj();
        aniobj.addnewele();
    }
    if (msg.is_right() && msg.is_down())
    {
        aniobj.updateobj();
        aniobj.fly();
    }
    }

    closegraph();
    return 0;
}
