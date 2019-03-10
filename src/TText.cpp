#include "../include/TText.h"
#define BufLength 90
static char StrBuf[BufLength + 1]; //Буфер для ввода строк
static int TextLevel;              // номер текущего уровня текста

TText::TText(PTTextLink pl)
{
    if (pl == NULL)
        pl = new TTextLink();
    pFirst = pl;
}
// Navigation
int TText::GoFirstLink()
{
    while (!Path.empty())
        Path.pop();
    pCurrent = pFirst;
    if (pCurrent == NULL)
        SetRetCode(TextError);
    else
        SetRetCode(TextOK);
    return RetCode;
}
int TText::GoDownLink() //go to next string on Down
{
    SetRetCode(TextError);
    if (pCurrent != NULL)
        if (pCurrent->pDown != NULL)
        {
            Path.push(pCurrent);
            pCurrent = pCurrent->pDown;
            SetRetCode(TextOK);
        }
    return RetCode;
}
int TText::GoNextLink() // go to next string on Next
{
    SetRetCode(TextError);
    if (pCurrent != NULL)
        if (pCurrent->pNext != NULL)
        {
            Path.push(pCurrent);
            pCurrent = pCurrent->pNext;
            SetRetCode(TextOK);
        }
    return RetCode;
}
int TText::GoPrevLink() // go to previous string
{
    if (Path.empty())
        SetRetCode(TextNoPrev);
    else
    {
        pCurrent = Path.top();
        Path.pop();
        SetRetCode(TextOK);
    }
    return RetCode;
}

//Access

string TText::GetLine() // reading current string
{
    if (pCurrent == NULL)
        return string("");
    else
        return string(pCurrent->Str);
}
void TText::SetLine(string s) // replacement current string
{
    if (pCurrent == NULL)
        SetRetCode(TextError);
    else
        strncpy(pCurrent->Str, s.c_str(), TextLineLength);
    pCurrent->Str[TextLineLength - 1] = '\0';
}

//     Modification

void TText::InsDownLine(string s) //insertion string to Down(SubLevel)
{
    if (pCurrent == NULL)
        SetRetCode(TextError);
    else
    {
        PTTextLink pd = pCurrent->pDown;
        PTTextLink pl = new TTextLink(NULL, pd, NULL); // я думаю при инициализации можно передать s.c_str()!!!!!
        strncpy(pl->Str, s.c_str(), TextLineLength);
        pl->Str[TextLineLength - 1] = '\0'; // set 0 if s.length > Str.length
        pCurrent->pDown = pl;
        SetRetCode(TextOK);
    }
}
void TText::InsDownSection(string s) // insertion section to Down (SubLevel)
{
    if (pCurrent == NULL)
        SetRetCode(TextError);
    else
    {
        PTTextLink pd = pCurrent->pDown;
        PTTextLink pl = new TTextLink(NULL, NULL, pd);
        strncpy(pl->Str, s.c_str(), TextLineLength);
        pl->Str[TextLineLength - 1] = '\0'; // set 0 if s.length > Str.length
        pCurrent->pDown = pl;
        SetRetCode(TextOK);
    }
}
void TText::InsNextLine(string s) // insert string to cur level
{
    if(pCurrent == NULL)
        SetRetCode(TextError);
    else
    {
        PTTextLink pl = new TTextLink(NULL, pCurrent->pNext, NULL);
        strncpy(pl->Str,s.c_str(),TextLineLength);
        pl->Str[TextLineLength - 1] = '\0';
        pCurrent->pNext = pl;
        SetRetCode(TextOK);
    }
}
void TText::InsNextSection(string s)
{
        if(pCurrent == NULL)
        SetRetCode(TextError);
    else
    {
        PTTextLink pl = new TTextLink(NULL, NULL, pCurrent->pNext);
        strncpy(pl->Str,s.c_str(),TextLineLength);
        pl->Str[TextLineLength - 1] = '\0';
        pCurrent->pNext = pl;
        SetRetCode(TextOK);
    }
}
