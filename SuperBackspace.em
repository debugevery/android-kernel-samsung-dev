/**
 *       �q����r
 *       {/ �� ��\}
 *       (  (oo)  )
 *        �����
 *      �� ��  �� Ʒ
 *
 * 2006 ���׽� Ding Zhaojie
 * zhaojie.ding@gmail.com
 *
 * SuperBackspace Version 0.1beta
 *
 * ����SourceInsightԭ�е�Backspace���ܣ�ϣ����ˣ�
 * �����˶�˫�ֽں��ֵ�֧�֣���ɾ�����ֵ�ʱ��Ҳ��ͬʱɾ�����ֵĸ��ֽڶ���������������
 * �ܹ��Թ���ں����м����������Զ�����
 *
 * ��װ��
 * �� ������SourceInsight��װĿ¼��
 * �� Project��Open Project����Base��Ŀ��
 * �� �����ƹ�ȥ��SuperBackspace.em�����Base��Ŀ��
 * �� ����SourceInsight��
 * �� Options��Key Assignments����Marco: SuperBackspace�󶨵�BackSpace����
 * �� Enjoy����
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
macro SuperBackspace()
{
    hwnd = GetCurrentWnd();
    hbuf = GetCurrentBuf();

    if (hbuf == 0)
        stop;   // empty buffer

    // get current cursor postion
    ipos = GetWndSelIchFirst(hwnd);

    // get current line number
    ln = GetBufLnCur(hbuf);

    if ((GetBufSelText(hbuf) != "") || (GetWndSelLnFirst(hwnd) != GetWndSelLnLast(hwnd))) {
        // sth. was selected, del selection
        SetBufSelText(hbuf, " ");  // stupid & buggy sourceinsight :(
        // del the " "
        SuperBackspace(1);
        stop;
    }

    // copy current line
    text = GetBufLine(hbuf, ln);

    // get string length
    len = strlen(text);

    // if the cursor is at the start of line, combine with prev line
    if (ipos == 0 || len == 0) {
        if (ln <= 0)
            stop;   // top of file
        ln = ln - 1;    // do not use "ln--" for compatibility with older versions
        prevline = GetBufLine(hbuf, ln);
        prevlen = strlen(prevline);
        // combine two lines
        text = cat(prevline, text);
        // del two lines
        DelBufLine(hbuf, ln);
        DelBufLine(hbuf, ln);
        // insert the combined one
        InsBufLine(hbuf, ln, text);
        // set the cursor position
        SetBufIns(hbuf, ln, prevlen);
        stop;
    }

    num = 1; // del one char
    if (ipos >= 1) {
        // process Chinese character
        i = ipos;
        count = 0;
        while (AsciiFromChar(text[i - 1]) >= 160) {
            i = i - 1;
            count = count + 1;
            if (i == 0)
                break;
        }
        if (count > 0) {
            // I think it might be a two-byte character
            num = 2;
            // This idiot does not support mod and bitwise operators
            if ((count / 2 * 2 != count) && (ipos < len))
                ipos = ipos + 1;    // adjust cursor position
        }
    }

    // keeping safe
    if (ipos - num < 0)
        num = ipos;

    // del char(s)
    text = cat(strmid(text, 0, ipos - num), strmid(text, ipos, len));
    DelBufLine(hbuf, ln);
    InsBufLine(hbuf, ln, text);
    SetBufIns(hbuf, ln, ipos - num);
    stop;
}

