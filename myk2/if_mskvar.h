<?xml version="1.0" encoding="iso-8859-1"?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en-US" lang="en-US">
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1"/>
    <title>if_mskvar.h</title>
    <link rel="icon" href="/openbsd/img/icon.png" type="image/png"/>
    <link rel="stylesheet" type="text/css" href="/openbsd/style.css"/>
    <link rel="stylesheet" type="text/css" href="/openbsd/print.css" media="print" />
    <link rel="alternate stylesheet" type="text/css" media="all" title="Paper White" href="/openbsd/print.css"/>
</head>
<body><div id="page">
<form action="/openbsd/search">
    <div id="header">
        <div id="MastheadLogo"> <h1> OpenGrok </h1> </div>
        <div id="pagetitle"><b id="filename">if_mskvar.h</b><br/></div>
    </div>
<div id="Masthead"><tt><a href="/openbsd/xref/">xref</a>: /<a href="/openbsd/xref/src/">src</a>/<a href="/openbsd/xref/src/sys/">sys</a>/<a href="/openbsd/xref/src/sys/dev/">dev</a>/<a href="/openbsd/xref/src/sys/dev/pci/">pci</a>/<a href="/openbsd/xref/src/sys/dev/pci/if_mskvar.h">if_mskvar.h</a></tt></div>    
<div id="bar"><a href="/openbsd" id="home">Home</a> | 
<a id="history" href="/openbsd/history/src/sys/dev/pci/if_mskvar.h">History</a> | <a id="download" href="/openbsd/raw/src/sys/dev/pci/if_mskvar.h">Download</a> |  <input id="search" name="q" class="q"/>
<input type="submit" value="Search" class="submit"/><input type="checkbox" name="path" value="/src/sys/dev/pci"/> only in <b>pci</b></div></form>
<div id="src"><pre><a class="l" name="1">      1 </a><span class="c">/*	$OpenBSD: <a href="/openbsd/s?path=if_mskvar.h">if_mskvar.h</a>,v 1.6 2007/11/25 00:27:44 kettenis Exp $	*/</span>
<a class="l" name="2">      2 </a><span class="c">/*	$NetBSD: <a href="/openbsd/s?path=if_skvar.h">if_skvar.h</a>,v 1.6 2005/05/30 04:35:22 christos Exp $	*/</span>
<a class="l" name="3">      3 </a>
<a class="l" name="4">      4 </a><span class="c">/*-
<a class="l" name="5">      5 </a> * Copyright (c) 2003 The NetBSD Foundation, Inc.
<a class="l" name="6">      6 </a> * All rights reserved.
<a class="l" name="7">      7 </a> *
<a class="l" name="8">      8 </a> * Redistribution and use in source and binary forms, with or without
<a class="l" name="9">      9 </a> * modification, are permitted provided that the following conditions
<a class="hl" name="10">     10 </a> * are met:
<a class="l" name="11">     11 </a> * 1. Redistributions of source code must retain the above copyright
<a class="l" name="12">     12 </a> *    notice, this list of conditions and the following disclaimer.
<a class="l" name="13">     13 </a> * 2. Redistributions in binary form must reproduce the above copyright
<a class="l" name="14">     14 </a> *    notice, this list of conditions and the following disclaimer in the
<a class="l" name="15">     15 </a> *    documentation <a href="/openbsd/s?path=and/">and</a>/<a href="/openbsd/s?path=and/or">or</a> other materials provided with the distribution.
<a class="l" name="16">     16 </a> * 3. All advertising materials mentioning features or use of this software
<a class="l" name="17">     17 </a> *    must display the following acknowledgement:
<a class="l" name="18">     18 </a> *	This product includes software developed by the NetBSD
<a class="l" name="19">     19 </a> *	Foundation, Inc. and its contributors.
<a class="hl" name="20">     20 </a> * 4. Neither the name of The NetBSD Foundation nor the names of its
<a class="l" name="21">     21 </a> *    contributors may be used to endorse or promote products derived
<a class="l" name="22">     22 </a> *    from this software without specific prior written permission.
<a class="l" name="23">     23 </a> *
<a class="l" name="24">     24 </a> * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
<a class="l" name="25">     25 </a> * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
<a class="l" name="26">     26 </a> * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
<a class="l" name="27">     27 </a> * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
<a class="l" name="28">     28 </a> * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
<a class="l" name="29">     29 </a> * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
<a class="hl" name="30">     30 </a> * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
<a class="l" name="31">     31 </a> * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
<a class="l" name="32">     32 </a> * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
<a class="l" name="33">     33 </a> * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
<a class="l" name="34">     34 </a> * POSSIBILITY OF SUCH DAMAGE.
<a class="l" name="35">     35 </a> */</span>
<a class="l" name="36">     36 </a><span class="c">/*	$OpenBSD: <a href="/openbsd/s?path=if_mskvar.h">if_mskvar.h</a>,v 1.6 2007/11/25 00:27:44 kettenis Exp $	*/</span>
<a class="l" name="37">     37 </a>
<a class="l" name="38">     38 </a><span class="c">/*
<a class="l" name="39">     39 </a> * Copyright (c) 1997, 1998, 1999, 2000
<a class="hl" name="40">     40 </a> *	Bill Paul &lt;wpaul (at) ctr.columbia.edu&gt;.  All rights reserved.
<a class="l" name="41">     41 </a> *
<a class="l" name="42">     42 </a> * Redistribution and use in source and binary forms, with or without
<a class="l" name="43">     43 </a> * modification, are permitted provided that the following conditions
<a class="l" name="44">     44 </a> * are met:
<a class="l" name="45">     45 </a> * 1. Redistributions of source code must retain the above copyright
<a class="l" name="46">     46 </a> *    notice, this list of conditions and the following disclaimer.
<a class="l" name="47">     47 </a> * 2. Redistributions in binary form must reproduce the above copyright
<a class="l" name="48">     48 </a> *    notice, this list of conditions and the following disclaimer in the
<a class="l" name="49">     49 </a> *    documentation <a href="/openbsd/s?path=and/">and</a>/<a href="/openbsd/s?path=and/or">or</a> other materials provided with the distribution.
<a class="hl" name="50">     50 </a> * 3. All advertising materials mentioning features or use of this software
<a class="l" name="51">     51 </a> *    must display the following acknowledgement:
<a class="l" name="52">     52 </a> *	This product includes software developed by Bill Paul.
<a class="l" name="53">     53 </a> * 4. Neither the name of the author nor the names of any co-contributors
<a class="l" name="54">     54 </a> *    may be used to endorse or promote products derived from this software
<a class="l" name="55">     55 </a> *    without specific prior written permission.
<a class="l" name="56">     56 </a> *
<a class="l" name="57">     57 </a> * THIS SOFTWARE IS PROVIDED BY Bill Paul AND CONTRIBUTORS ``AS IS'' AND
<a class="l" name="58">     58 </a> * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
<a class="l" name="59">     59 </a> * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
<a class="hl" name="60">     60 </a> * ARE DISCLAIMED.  IN NO EVENT SHALL Bill Paul OR THE VOICES IN HIS HEAD
<a class="l" name="61">     61 </a> * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
<a class="l" name="62">     62 </a> * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
<a class="l" name="63">     63 </a> * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
<a class="l" name="64">     64 </a> * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
<a class="l" name="65">     65 </a> * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
<a class="l" name="66">     66 </a> * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
<a class="l" name="67">     67 </a> * THE POSSIBILITY OF SUCH DAMAGE.
<a class="l" name="68">     68 </a> *
<a class="l" name="69">     69 </a> * $FreeBSD: /<a href="/openbsd/s?path=/c/">c</a>/<a href="/openbsd/s?path=/c/ncvs/">ncvs</a>/<a href="/openbsd/s?path=/c/ncvs/src/">src</a>/<a href="/openbsd/s?path=/c/ncvs/src/sys/">sys</a>/<a href="/openbsd/s?path=/c/ncvs/src/sys/pci/">pci</a>/<a href="/openbsd/s?path=/c/ncvs/src/sys/pci/if_skreg.h">if_skreg.h</a>,v 1.9 2000/04/22 02:16:37 wpaul Exp $
<a class="hl" name="70">     70 </a> */</span>
<a class="l" name="71">     71 </a>
<a class="l" name="72">     72 </a><span class="c">/*
<a class="l" name="73">     73 </a> * Copyright (c) 2003 Nathan L. Binkert &lt;binkertn (at) umich.edu&gt;
<a class="l" name="74">     74 </a> *
<a class="l" name="75">     75 </a> * Permission to use, copy, modify, and distribute this software for any
<a class="l" name="76">     76 </a> * purpose with or without fee is hereby granted, provided that the above
<a class="l" name="77">     77 </a> * copyright notice and this permission notice appear in all copies.
<a class="l" name="78">     78 </a> *
<a class="l" name="79">     79 </a> * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
<a class="hl" name="80">     80 </a> * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
<a class="l" name="81">     81 </a> * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
<a class="l" name="82">     82 </a> * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
<a class="l" name="83">     83 </a> * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
<a class="l" name="84">     84 </a> * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
<a class="l" name="85">     85 </a> * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
<a class="l" name="86">     86 </a> */</span>
<a class="l" name="87">     87 </a>
<a class="l" name="88">     88 </a>#<b>ifndef</b> <a class="f" href="#_DEV_PCI_IF_MSKVAR_H_">_DEV_PCI_IF_MSKVAR_H_</a>
<a class="l" name="89">     89 </a>#<b>define</b> <a class="d" name="_DEV_PCI_IF_MSKVAR_H_">_DEV_PCI_IF_MSKVAR_H_</a>
<a class="hl" name="90">     90 </a>
<a class="l" name="91">     91 </a><b>struct</b> <a class="d" name="sk_jpool_entry">sk_jpool_entry</a> {
<a class="l" name="92">     92 </a>	<b>int</b>                             <a class="d" name="slot">slot</a>;
<a class="l" name="93">     93 </a>	<a href="/openbsd/s?defs=LIST_ENTRY">LIST_ENTRY</a>(<a class="f" href="#sk_jpool_entry">sk_jpool_entry</a>)	<a class="d" name="jpool_entries">jpool_entries</a>;
<a class="l" name="94">     94 </a>};
<a class="l" name="95">     95 </a>
<a class="l" name="96">     96 </a><b>struct</b> <a class="d" name="sk_chain">sk_chain</a> {
<a class="l" name="97">     97 </a>	<b>void</b>			*<a class="d" name="sk_le">sk_le</a>;
<a class="l" name="98">     98 </a>	<b>struct</b> <a href="/openbsd/s?defs=mbuf">mbuf</a>		*<a class="d" name="sk_mbuf">sk_mbuf</a>;
<a class="l" name="99">     99 </a>	<b>struct</b> <a class="f" href="#sk_chain">sk_chain</a>		*<a class="d" name="sk_next">sk_next</a>;
<a class="hl" name="100">    100 </a>};
<a class="l" name="101">    101 </a>
<a class="l" name="102">    102 </a><span class="c">/*
<a class="l" name="103">    103 </a> * Number of DMA segments in a TxCB. Note that this is carefully
<a class="l" name="104">    104 </a> * chosen to make the total struct size an even power of two. It's
<a class="l" name="105">    105 </a> * critical that no TxCB be split across a page boundary since
<a class="l" name="106">    106 </a> * no attempt is made to allocate physically contiguous memory.
<a class="l" name="107">    107 </a> *
<a class="l" name="108">    108 </a> */</span>
<a class="l" name="109">    109 </a>#<b>define</b> <a class="d" name="SK_NTXSEG">SK_NTXSEG</a>      <span class="n">30</span>
<a class="hl" name="110">    110 </a>
<a class="l" name="111">    111 </a><b>struct</b> <a class="d" name="sk_txmap_entry">sk_txmap_entry</a> {
<a class="l" name="112">    112 </a>	<a href="/openbsd/s?defs=bus_dmamap_t">bus_dmamap_t</a>			<a class="d" name="dmamap">dmamap</a>;
<a class="l" name="113">    113 </a>	<a href="/openbsd/s?defs=SIMPLEQ_ENTRY">SIMPLEQ_ENTRY</a>(<a class="f" href="#sk_txmap_entry">sk_txmap_entry</a>)	<a class="d" name="link">link</a>;
<a class="l" name="114">    114 </a>};
<a class="l" name="115">    115 </a>
<a class="l" name="116">    116 </a><b>struct</b> <a class="d" name="msk_chain_data">msk_chain_data</a> {
<a class="l" name="117">    117 </a>	<b>struct</b> <a class="f" href="#sk_chain">sk_chain</a>		<a class="d" name="sk_tx_chain">sk_tx_chain</a>[<a href="/openbsd/s?defs=MSK_TX_RING_CNT">MSK_TX_RING_CNT</a>];
<a class="l" name="118">    118 </a>	<b>struct</b> <a class="f" href="#sk_chain">sk_chain</a>		<a class="d" name="sk_rx_chain">sk_rx_chain</a>[<a href="/openbsd/s?defs=MSK_RX_RING_CNT">MSK_RX_RING_CNT</a>];
<a class="l" name="119">    119 </a>	<b>struct</b> <a class="f" href="#sk_txmap_entry">sk_txmap_entry</a>	*<a class="d" name="sk_tx_map">sk_tx_map</a>[<a href="/openbsd/s?defs=MSK_TX_RING_CNT">MSK_TX_RING_CNT</a>];
<a class="hl" name="120">    120 </a>	<a href="/openbsd/s?defs=bus_dmamap_t">bus_dmamap_t</a>		<a class="d" name="sk_rx_map">sk_rx_map</a>[<a href="/openbsd/s?defs=MSK_RX_RING_CNT">MSK_RX_RING_CNT</a>];
<a class="l" name="121">    121 </a>	<a href="/openbsd/s?defs=bus_dmamap_t">bus_dmamap_t</a>		<a class="d" name="sk_rx_jumbo_map">sk_rx_jumbo_map</a>;
<a class="l" name="122">    122 </a>	<b>int</b>			<a class="d" name="sk_tx_prod">sk_tx_prod</a>;
<a class="l" name="123">    123 </a>	<b>int</b>			<a class="d" name="sk_tx_cons">sk_tx_cons</a>;
<a class="l" name="124">    124 </a>	<b>int</b>			<a class="d" name="sk_tx_cnt">sk_tx_cnt</a>;
<a class="l" name="125">    125 </a>	<b>int</b>			<a class="d" name="sk_rx_prod">sk_rx_prod</a>;
<a class="l" name="126">    126 </a>	<b>int</b>			<a class="d" name="sk_rx_cons">sk_rx_cons</a>;
<a class="l" name="127">    127 </a>	<b>int</b>			<a class="d" name="sk_rx_cnt">sk_rx_cnt</a>;
<a class="l" name="128">    128 </a>	<span class="c">/* Stick the jumbo mem management stuff here too. */</span>
<a class="l" name="129">    129 </a>	<a href="/openbsd/s?defs=caddr_t">caddr_t</a>			<a class="d" name="sk_jslots">sk_jslots</a>[<a href="/openbsd/s?defs=MSK_JSLOTS">MSK_JSLOTS</a>];
<a class="hl" name="130">    130 </a>	<b>void</b>			*<a class="d" name="sk_jumbo_buf">sk_jumbo_buf</a>;
<a class="l" name="131">    131 </a>};
<a class="l" name="132">    132 </a>
<a class="l" name="133">    133 </a><b>struct</b> <a class="d" name="msk_ring_data">msk_ring_data</a> {
<a class="l" name="134">    134 </a>	<b>struct</b> <a href="/openbsd/s?defs=msk_tx_desc">msk_tx_desc</a>	<a class="d" name="sk_tx_ring">sk_tx_ring</a>[<a href="/openbsd/s?defs=MSK_TX_RING_CNT">MSK_TX_RING_CNT</a>];
<a class="l" name="135">    135 </a>	<b>struct</b> <a href="/openbsd/s?defs=msk_rx_desc">msk_rx_desc</a>	<a class="d" name="sk_rx_ring">sk_rx_ring</a>[<a href="/openbsd/s?defs=MSK_RX_RING_CNT">MSK_RX_RING_CNT</a>];
<a class="l" name="136">    136 </a>};
<a class="l" name="137">    137 </a>
<a class="l" name="138">    138 </a>#<b>define</b> <a class="d" name="MSK_TX_RING_ADDR">MSK_TX_RING_ADDR</a>(<a href="/openbsd/s?defs=sc">sc</a>, i) \
<a class="l" name="139">    139 </a>    ((<a href="/openbsd/s?defs=sc">sc</a>)-&gt;<a class="f" href="#sk_ring_map">sk_ring_map</a>-&gt;<a href="/openbsd/s?defs=dm_segs">dm_segs</a>[<span class="n">0</span>].<a href="/openbsd/s?defs=ds_addr">ds_addr</a> + \
<a class="hl" name="140">    140 </a>     <a href="/openbsd/s?defs=offsetof">offsetof</a>(<b>struct</b> <a class="f" href="#msk_ring_data">msk_ring_data</a>, <a class="f" href="#sk_tx_ring">sk_tx_ring</a>[(i)]))
<a class="l" name="141">    141 </a>
<a class="l" name="142">    142 </a>#<b>define</b> <a class="d" name="MSK_RX_RING_ADDR">MSK_RX_RING_ADDR</a>(<a href="/openbsd/s?defs=sc">sc</a>, i) \
<a class="l" name="143">    143 </a>    ((<a href="/openbsd/s?defs=sc">sc</a>)-&gt;<a class="f" href="#sk_ring_map">sk_ring_map</a>-&gt;<a href="/openbsd/s?defs=dm_segs">dm_segs</a>[<span class="n">0</span>].<a href="/openbsd/s?defs=ds_addr">ds_addr</a> + \
<a class="l" name="144">    144 </a>     <a href="/openbsd/s?defs=offsetof">offsetof</a>(<b>struct</b> <a class="f" href="#msk_ring_data">msk_ring_data</a>, <a class="f" href="#sk_rx_ring">sk_rx_ring</a>[(i)]))
<a class="l" name="145">    145 </a>
<a class="l" name="146">    146 </a>#<b>define</b> <a class="d" name="MSK_CDOFF">MSK_CDOFF</a>(x)	<a href="/openbsd/s?defs=offsetof">offsetof</a>(<b>struct</b> <a class="f" href="#msk_ring_data">msk_ring_data</a>, x)
<a class="l" name="147">    147 </a>#<b>define</b> <a class="d" name="MSK_CDTXOFF">MSK_CDTXOFF</a>(x)	<a class="f" href="#MSK_CDOFF">MSK_CDOFF</a>(<a class="f" href="#sk_tx_ring">sk_tx_ring</a>[(x)])
<a class="l" name="148">    148 </a>#<b>define</b> <a class="d" name="MSK_CDRXOFF">MSK_CDRXOFF</a>(x)	<a class="f" href="#MSK_CDOFF">MSK_CDOFF</a>(<a class="f" href="#sk_rx_ring">sk_rx_ring</a>[(x)])
<a class="l" name="149">    149 </a>#<b>define</b> <a class="d" name="MSK_CDSTOFF">MSK_CDSTOFF</a>(x)	((x) * <b>sizeof</b>(<b>struct</b> <a href="/openbsd/s?defs=msk_status_desc">msk_status_desc</a>))
<a class="hl" name="150">    150 </a>
<a class="l" name="151">    151 </a>#<b>define</b> <a class="d" name="MSK_CDTXSYNC">MSK_CDTXSYNC</a>(<a href="/openbsd/s?defs=sc">sc</a>, x, n, <a href="/openbsd/s?defs=ops">ops</a>)					\
<a class="l" name="152">    152 </a><b>do</b> {									\
<a class="l" name="153">    153 </a>	<b>int</b> <a href="/openbsd/s?defs=__x">__x</a>, <a href="/openbsd/s?defs=__n">__n</a>;							\
<a class="l" name="154">    154 </a>									\
<a class="l" name="155">    155 </a>	<a href="/openbsd/s?defs=__x">__x</a> = (x);							\
<a class="l" name="156">    156 </a>	<a href="/openbsd/s?defs=__n">__n</a> = (n);							\
<a class="l" name="157">    157 </a>									\
<a class="l" name="158">    158 </a>	<span class="c">/* If it will wrap around, sync to the end of the ring. */</span>	\
<a class="l" name="159">    159 </a>	<b>if</b> ((<a href="/openbsd/s?defs=__x">__x</a> + <a href="/openbsd/s?defs=__n">__n</a>) &gt; <a href="/openbsd/s?defs=MSK_TX_RING_CNT">MSK_TX_RING_CNT</a>) {				\
<a class="hl" name="160">    160 </a>		<a href="/openbsd/s?defs=bus_dmamap_sync">bus_dmamap_sync</a>((<a href="/openbsd/s?defs=sc">sc</a>)-&gt;<span class="mf">sk_softc</span>-&gt;<a class="f" href="#sc_dmatag">sc_dmatag</a>,		\
<a class="l" name="161">    161 </a>		    (<a href="/openbsd/s?defs=sc">sc</a>)-&gt;<a class="f" href="#sk_ring_map">sk_ring_map</a>, <a class="f" href="#MSK_CDTXOFF">MSK_CDTXOFF</a>(<a href="/openbsd/s?defs=__x">__x</a>),		\
<a class="l" name="162">    162 </a>		    <b>sizeof</b>(<b>struct</b> <a href="/openbsd/s?defs=msk_tx_desc">msk_tx_desc</a>) * (<a href="/openbsd/s?defs=MSK_TX_RING_CNT">MSK_TX_RING_CNT</a> - <a href="/openbsd/s?defs=__x">__x</a>), \
<a class="l" name="163">    163 </a>		    (<a href="/openbsd/s?defs=ops">ops</a>));						\
<a class="l" name="164">    164 </a>		<a href="/openbsd/s?defs=__n">__n</a> -= (<a href="/openbsd/s?defs=MSK_TX_RING_CNT">MSK_TX_RING_CNT</a> - <a href="/openbsd/s?defs=__x">__x</a>);				\
<a class="l" name="165">    165 </a>		<a href="/openbsd/s?defs=__x">__x</a> = <span class="n">0</span>;						\
<a class="l" name="166">    166 </a>	}								\
<a class="l" name="167">    167 </a>									\
<a class="l" name="168">    168 </a>	<span class="c">/* Now sync whatever is left. */</span>				\
<a class="l" name="169">    169 </a>	<a href="/openbsd/s?defs=bus_dmamap_sync">bus_dmamap_sync</a>((<a href="/openbsd/s?defs=sc">sc</a>)-&gt;<span class="mf">sk_softc</span>-&gt;<a class="f" href="#sc_dmatag">sc_dmatag</a>, (<a href="/openbsd/s?defs=sc">sc</a>)-&gt;<a class="f" href="#sk_ring_map">sk_ring_map</a>,	\
<a class="hl" name="170">    170 </a>	    <a class="f" href="#MSK_CDTXOFF">MSK_CDTXOFF</a>((<a href="/openbsd/s?defs=__x">__x</a>)), <b>sizeof</b>(<b>struct</b> <a href="/openbsd/s?defs=msk_tx_desc">msk_tx_desc</a>) * <a href="/openbsd/s?defs=__n">__n</a>, (<a href="/openbsd/s?defs=ops">ops</a>)); \
<a class="l" name="171">    171 </a>} <b>while</b> (<span class="c">/*CONSTCOND*/</span><span class="n">0</span>)
<a class="l" name="172">    172 </a>
<a class="l" name="173">    173 </a>#<b>define</b> <a class="d" name="MSK_CDRXSYNC">MSK_CDRXSYNC</a>(<a href="/openbsd/s?defs=sc">sc</a>, x, <a href="/openbsd/s?defs=ops">ops</a>)					\
<a class="l" name="174">    174 </a><b>do</b> {									\
<a class="l" name="175">    175 </a>	<a href="/openbsd/s?defs=bus_dmamap_sync">bus_dmamap_sync</a>((<a href="/openbsd/s?defs=sc">sc</a>)-&gt;<span class="mf">sk_softc</span>-&gt;<a class="f" href="#sc_dmatag">sc_dmatag</a>, (<a href="/openbsd/s?defs=sc">sc</a>)-&gt;<a class="f" href="#sk_ring_map">sk_ring_map</a>,	\
<a class="l" name="176">    176 </a>	    <a class="f" href="#MSK_CDRXOFF">MSK_CDRXOFF</a>((x)), <b>sizeof</b>(<b>struct</b> <a href="/openbsd/s?defs=msk_rx_desc">msk_rx_desc</a>), (<a href="/openbsd/s?defs=ops">ops</a>));	\
<a class="l" name="177">    177 </a>} <b>while</b> (<span class="c">/*CONSTCOND*/</span><span class="n">0</span>)
<a class="l" name="178">    178 </a>
<a class="l" name="179">    179 </a>#<b>define</b> <a class="d" name="MSK_CDSTSYNC">MSK_CDSTSYNC</a>(<a href="/openbsd/s?defs=sc">sc</a>, x, <a href="/openbsd/s?defs=ops">ops</a>)					\
<a class="hl" name="180">    180 </a><b>do</b> {									\
<a class="l" name="181">    181 </a>	<a href="/openbsd/s?defs=bus_dmamap_sync">bus_dmamap_sync</a>((<a href="/openbsd/s?defs=sc">sc</a>)-&gt;<a class="f" href="#sc_dmatag">sc_dmatag</a>, (<a href="/openbsd/s?defs=sc">sc</a>)-&gt;<a class="f" href="#sk_status_map">sk_status_map</a>,		\
<a class="l" name="182">    182 </a>	    <a class="f" href="#MSK_CDSTOFF">MSK_CDSTOFF</a>((x)), <b>sizeof</b>(<b>struct</b> <a href="/openbsd/s?defs=msk_status_desc">msk_status_desc</a>), (<a href="/openbsd/s?defs=ops">ops</a>));	\
<a class="l" name="183">    183 </a>} <b>while</b> (<span class="c">/*CONSTCOND*/</span><span class="n">0</span>)
<a class="l" name="184">    184 </a>
<a class="l" name="185">    185 </a>#<b>define</b> <a class="d" name="SK_INC">SK_INC</a>(x, y)	(x) = (x + <span class="n">1</span>) % y
<a class="l" name="186">    186 </a>
<a class="l" name="187">    187 </a><span class="c">/* Forward decl. */</span>
<a class="l" name="188">    188 </a><b>struct</b> <a class="f" href="#sk_if_softc">sk_if_softc</a>;
<a class="l" name="189">    189 </a>
<a class="hl" name="190">    190 </a><span class="c">/* Softc for the Yukon-II controller. */</span>
<a class="l" name="191">    191 </a><b>struct</b> <a class="d" name="sk_softc">sk_softc</a> {
<a class="l" name="192">    192 </a>	<b>struct</b> <a href="/openbsd/s?defs=device">device</a>		<a class="d" name="sk_dev">sk_dev</a>;		<span class="c">/* generic device */</span>
<a class="l" name="193">    193 </a>	<a href="/openbsd/s?defs=bus_space_handle_t">bus_space_handle_t</a>	<a class="d" name="sk_bhandle">sk_bhandle</a>;	<span class="c">/* bus space handle */</span>
<a class="l" name="194">    194 </a>	<a href="/openbsd/s?defs=bus_space_tag_t">bus_space_tag_t</a>		<a class="d" name="sk_btag">sk_btag</a>;	<span class="c">/* bus space tag */</span>
<a class="l" name="195">    195 </a>	<a href="/openbsd/s?defs=bus_size_t">bus_size_t</a>		<a class="d" name="sk_bsize">sk_bsize</a>;	<span class="c">/* bus space size */</span>
<a class="l" name="196">    196 </a>	<b>void</b>			*<a class="d" name="sk_intrhand">sk_intrhand</a>;	<span class="c">/* irq handler handle */</span>
<a class="l" name="197">    197 </a>	<a href="/openbsd/s?defs=pci_chipset_tag_t">pci_chipset_tag_t</a>	<a class="d" name="sk_pc">sk_pc</a>;
<a class="l" name="198">    198 </a>	<a href="/openbsd/s?defs=u_int8_t">u_int8_t</a>		<a class="d" name="sk_fibertype">sk_fibertype</a>;
<a class="l" name="199">    199 </a>	<a href="/openbsd/s?defs=u_int8_t">u_int8_t</a>		<a class="d" name="sk_type">sk_type</a>;
<a class="hl" name="200">    200 </a>	<a href="/openbsd/s?defs=u_int8_t">u_int8_t</a>		<a class="d" name="sk_rev">sk_rev</a>;
<a class="l" name="201">    201 </a>	<a href="/openbsd/s?defs=u_int8_t">u_int8_t</a>		<a class="d" name="sk_macs">sk_macs</a>;	<span class="c">/* # of MACs */</span>
<a class="l" name="202">    202 </a>	<b>char</b>			*<a class="d" name="sk_name">sk_name</a>;
<a class="l" name="203">    203 </a>	<a href="/openbsd/s?defs=u_int32_t">u_int32_t</a>		<a class="d" name="sk_ramsize">sk_ramsize</a>;	<span class="c">/* amount of RAM on NIC */</span>
<a class="l" name="204">    204 </a>	<a href="/openbsd/s?defs=u_int32_t">u_int32_t</a>		<a class="d" name="sk_intrmask">sk_intrmask</a>;
<a class="l" name="205">    205 </a>	<a href="/openbsd/s?defs=bus_dma_tag_t">bus_dma_tag_t</a>		<a class="d" name="sc_dmatag">sc_dmatag</a>;
<a class="l" name="206">    206 </a>	<b>struct</b> <a class="f" href="#sk_if_softc">sk_if_softc</a>	*<a class="d" name="sk_if">sk_if</a>[<span class="n">2</span>];
<a class="l" name="207">    207 </a>	<b>struct</b> <a href="/openbsd/s?defs=msk_status_desc">msk_status_desc</a>	*<a class="d" name="sk_status_ring">sk_status_ring</a>;
<a class="l" name="208">    208 </a>	<a href="/openbsd/s?defs=bus_dmamap_t">bus_dmamap_t</a>		<a class="d" name="sk_status_map">sk_status_map</a>;
<a class="l" name="209">    209 </a>	<a href="/openbsd/s?defs=bus_dma_segment_t">bus_dma_segment_t</a>	<a class="d" name="sk_status_seg">sk_status_seg</a>;
<a class="hl" name="210">    210 </a>	<b>int</b>			<a class="d" name="sk_status_nseg">sk_status_nseg</a>;
<a class="l" name="211">    211 </a>	<b>int</b>			<a class="d" name="sk_status_idx">sk_status_idx</a>;
<a class="l" name="212">    212 </a>};
<a class="l" name="213">    213 </a>
<a class="l" name="214">    214 </a><span class="c">/* Softc for each logical interface */</span>
<a class="l" name="215">    215 </a><b>struct</b> <a class="d" name="sk_if_softc">sk_if_softc</a> {
<a class="l" name="216">    216 </a>	<b>struct</b> <a href="/openbsd/s?defs=device">device</a>		<a class="d" name="sk_dev">sk_dev</a>;		<span class="c">/* generic device */</span>
<a class="l" name="217">    217 </a>	<b>struct</b> <a class="d" name="arpcom">arpcom</a>		<a class="d" name="arpcom">arpcom</a>;		<span class="c">/* interface info */</span>
<a class="l" name="218">    218 </a>	<b>struct</b> <a href="/openbsd/s?defs=mii_data">mii_data</a>		<a class="d" name="sk_mii">sk_mii</a>;
<a class="l" name="219">    219 </a>	<a href="/openbsd/s?defs=u_int8_t">u_int8_t</a>		<a class="d" name="sk_port">sk_port</a>;	<span class="c">/* port # on controller */</span>
<a class="hl" name="220">    220 </a>	<a href="/openbsd/s?defs=u_int8_t">u_int8_t</a>		<a class="d" name="sk_xmac_rev">sk_xmac_rev</a>;	<span class="c">/* XMAC chip rev (B2 or C1) */</span>
<a class="l" name="221">    221 </a>	<a href="/openbsd/s?defs=u_int32_t">u_int32_t</a>		<a class="d" name="sk_rx_ramstart">sk_rx_ramstart</a>;
<a class="l" name="222">    222 </a>	<a href="/openbsd/s?defs=u_int32_t">u_int32_t</a>		<a class="d" name="sk_rx_ramend">sk_rx_ramend</a>;
<a class="l" name="223">    223 </a>	<a href="/openbsd/s?defs=u_int32_t">u_int32_t</a>		<a class="d" name="sk_tx_ramstart">sk_tx_ramstart</a>;
<a class="l" name="224">    224 </a>	<a href="/openbsd/s?defs=u_int32_t">u_int32_t</a>		<a class="d" name="sk_tx_ramend">sk_tx_ramend</a>;
<a class="l" name="225">    225 </a>	<b>int</b>			<a class="d" name="sk_cnt">sk_cnt</a>;
<a class="l" name="226">    226 </a>	<b>int</b>			<a class="d" name="sk_link">sk_link</a>;
<a class="l" name="227">    227 </a>	<b>struct</b> <a href="/openbsd/s?defs=timeout">timeout</a>		<a class="d" name="sk_tick_ch">sk_tick_ch</a>;
<a class="l" name="228">    228 </a>	<b>struct</b> <a class="f" href="#msk_chain_data">msk_chain_data</a>	<a class="d" name="sk_cdata">sk_cdata</a>;
<a class="l" name="229">    229 </a>	<b>struct</b> <a class="f" href="#msk_ring_data">msk_ring_data</a>	*<a class="d" name="sk_rdata">sk_rdata</a>;
<a class="hl" name="230">    230 </a>	<a href="/openbsd/s?defs=bus_dmamap_t">bus_dmamap_t</a>		<a class="d" name="sk_ring_map">sk_ring_map</a>;
<a class="l" name="231">    231 </a>	<a href="/openbsd/s?defs=bus_dma_segment_t">bus_dma_segment_t</a>	<a class="d" name="sk_ring_seg">sk_ring_seg</a>;
<a class="l" name="232">    232 </a>	<b>int</b>			<a class="d" name="sk_ring_nseg">sk_ring_nseg</a>;
<a class="l" name="233">    233 </a>	<b>int</b>			<a class="d" name="sk_status_idx">sk_status_idx</a>;
<a class="l" name="234">    234 </a>	<b>struct</b> <a class="d" name="sk_softc">sk_softc</a>		*<a class="d" name="sk_softc">sk_softc</a>;	<span class="c">/* parent controller */</span>
<a class="l" name="235">    235 </a>	<b>int</b>			<a class="d" name="sk_tx_bmu">sk_tx_bmu</a>;	<span class="c">/* TX BMU register */</span>
<a class="l" name="236">    236 </a>	<b>int</b>			<a class="d" name="sk_if_flags">sk_if_flags</a>;
<a class="l" name="237">    237 </a>	<a href="/openbsd/s?defs=LIST_HEAD">LIST_HEAD</a>(<a href="/openbsd/s?defs=__sk_jfreehead">__sk_jfreehead</a>, <a class="f" href="#sk_jpool_entry">sk_jpool_entry</a>)	<a class="d" name="sk_jfree_listhead">sk_jfree_listhead</a>;
<a class="l" name="238">    238 </a>	<a href="/openbsd/s?defs=LIST_HEAD">LIST_HEAD</a>(<a href="/openbsd/s?defs=__sk_jinusehead">__sk_jinusehead</a>, <a class="f" href="#sk_jpool_entry">sk_jpool_entry</a>)	<a class="d" name="sk_jinuse_listhead">sk_jinuse_listhead</a>;
<a class="l" name="239">    239 </a>	<a href="/openbsd/s?defs=SIMPLEQ_HEAD">SIMPLEQ_HEAD</a>(<a href="/openbsd/s?defs=__sk_txmaphead">__sk_txmaphead</a>, <a class="f" href="#sk_txmap_entry">sk_txmap_entry</a>)	<a class="d" name="sk_txmap_head">sk_txmap_head</a>;
<a class="hl" name="240">    240 </a>	<b>void</b>			*<a class="d" name="sk_sdhook">sk_sdhook</a>;
<a class="l" name="241">    241 </a>};
<a class="l" name="242">    242 </a>
<a class="l" name="243">    243 </a><b>struct</b> <a class="d" name="skc_attach_args">skc_attach_args</a> {
<a class="l" name="244">    244 </a>	<a href="/openbsd/s?defs=u_int16_t">u_int16_t</a>	<a class="d" name="skc_port">skc_port</a>;
<a class="l" name="245">    245 </a>	<a href="/openbsd/s?defs=u_int8_t">u_int8_t</a>	<a class="d" name="skc_type">skc_type</a>;
<a class="l" name="246">    246 </a>	<a href="/openbsd/s?defs=u_int8_t">u_int8_t</a>	<a class="d" name="skc_rev">skc_rev</a>;
<a class="l" name="247">    247 </a>};
<a class="l" name="248">    248 </a>
<a class="l" name="249">    249 </a>#<b>endif</b> <span class="c">/* _DEV_PCI_IF_MSKVAR_H_ */</span>
<a class="hl" name="250">    250 </a></pre></div><div id="Footer">
<p class="Center">
<a href="http://www.opensolaris.org/os/project/opengrok/"><img src="/source/img/servedby.png" alt="Served by OpenGrok" title="Served by OpenGrok"/></a>
</p>
</div>
</div>
</body>
</html>

