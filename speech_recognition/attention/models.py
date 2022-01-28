#!/usr/bin/env/python3
""" 
Library implementing attention model.

Authors
* Zhichao Li 2022

"""

import torch
import torch.nn as nn

import numpy as np

import logging

# TODO(zhichaoli) remove this to yaml
FORMAT = '%(asctime)s %(filename)s %(funcName)s %(lineno)d %(message)s'
logging.basicConfig(level=logging.INFO, format=FORMAT)


class MultiHeadAttentionLayer(nn.Module):
    """
    This class implements  multi head attention layer .
    Reference: Attention Is All You Need--NeurIPS2017.
    paper:  https://arxiv.org/pdf/1706.03762.pdf.

    Arguments:
    ---------

    Example:
    --------
    >>>>
    """

    def __init__(self, hid_dim, n_heads, dropout, device):
        super(MultiHeadAttentionLayer, self).__init__()

        assert hid_dim % n_heads == 0, "multi head attetion hid_dim must be divided with n_heads"

        self.device = device

        self.hid_dim = hid_dim
        self.n_heads = n_heads
        self.head_dim = hid_dim // n_heads

        self.fc_q = nn.Linear(hid_dim, hid_dim)
        self.fc_k = nn.Linear(hid_dim, hid_dim)
        self.fc_v = nn.Linear(hid_dim, hid_dim)
        self.fc_o = nn.Linear(hid_dim, hid_dim)

        self.dropout = nn.Dropout(dropout)
        self.scale = torch.sqrt(torch.FloatTensor([self.head_dim])).to(device)

    def forward(self, query, key, value, mask=None):
        """
        query shape: [batch, seq-len, hid_dim]
        key shape: [batch, seq-len, hid_dim]
        value shape: [batch, seq-len, hid_dim]
        mask: [batch, 1, 1, seq-len]

        """

        b_s = query.shape[0]
        # q shape: [batch, seq-len, hid_dim] -> [batch, seq-len, n_heads, hid_dim//n_heads]
        #          -> [batch, n_heads, seq-len, hid_dim//n_heads]
        q = self.fc_q(query).view(b_s, -1, self.n_heads,
                                  self.head_dim).permute(0, 2, 1, 3)
        # k shape: [batch, seq-len, hid_dim] -> [batch, seq-len, n_heads, hid_dim//n_heads]
        #          -> [batch, n_heads, seq-len, hid_dim//n_heads]
        k = self.fc_k(key).view(b_s, -1, self.n_heads,
                                self.head_dim).permute(0, 2, 1, 3)
        # v shape: [batch, seq-len, hid_dim] -> [batch, seq-len, n_heads, hid_dim//n_heads]
        #          -> [batch, n_heads, seq-len, hid_dim//n_heads]
        v = self.fc_v(value).view(b_s, -1, self.n_heads,
                                  self.head_dim).permute(0, 2, 1, 3)
        # att shape: [batch, n_heads, seq-len, seq-len]
        att = torch.matmul(q, k.permute(0, 1, 3, 2)) / self.scale

        if mask is not None:
            # att shape: [batch, n_heads, seq-len, seq-len]
            att = att.masked_fill(mask == 0, -np.inf)

        # attention shape: [batch, n_heads, seq-len, seq-len]
        attention = torch.softmax(att, dim=-1)

        # att shape: [batch, n_heads, seq-len, seq-len]
        att = self.dropout(attention)

        # out shape: [batch, n_heads, seq-len, hid_dim//n_heads] ->
        #            [batch, seq-len, n_heads, hid_dim//n_heads] ->
        #            [batch, seq-len, hid_dim]
        out = torch.matmul(att, v).permute(0, 2, 1, 3).contiguous().view(
            b_s, -1, self.hid_dim)

        # out shape: [batch, seq-len, hid_dim]
        out = self.fc_o(out)

        return out, attention


class PositionWiseFeedforwardLayer(nn.Module):
    """
    This class implements encoder for PositionWise Feed forward layer.

    Arguments
    ---------
    attn_dim : int
        Size of the attention feature.

    Example
    -------
    >>> 

    """

    def __init__(self, hid_dim, pf_dim, dropout, device):
        super().__init__()

        self.device = device

        self.fc_1 = nn.Linear(hid_dim, pf_dim)
        self.fc_2 = nn.Linear(pf_dim, hid_dim)
        self.dropout = nn.Dropout(dropout)

    def forward(self, x):
        """
        x shape: [batch, seq-len, hid_dim]
        """
        # x shape: [batch, seq-len, pf_dim]
        x = self.dropout(torch.relu(self.fc_1(x)))

        # x shape: [batch, seq-len, hid_dim]
        x = self.fc_2(x)

        return x


class EncoderLayer(nn.Module):
    """
    This class implements encoder for PositionWise Feed forward layer.

    Arguments
    ---------
    attn_dim : int
        Size of the attention feature.

    Example
    -------
    >>> 

    """

    def __init__(self, hid_dim, n_heads, pf_dim, dropout, device):
        super().__init__()

        self.device = device

        self.self_att_layer_norm = nn.LayerNorm(hid_dim)
        self.ff_layer_norm = nn.LayerNorm(hid_dim)
        self.self_attention = MultiHeadAttentionLayer(hid_dim, n_heads, dropout,
                                                      self.device)
        self.positionwise_feedforward = PositionWiseFeedforwardLayer(
            hid_dim, pf_dim, dropout, self.device)

        self.dropout = nn.Dropout(dropout)

    def forward(self, src, src_mask):
        """
        src shape: [batch, seq-len, hid_dim]
        src_mask: [batch, 1, 1, seq-len]

        """

        _src, _ = self.self_attention(src, src, src, src_mask)
        src = self.self_att_layer_norm(src + self.dropout(_src))

        _src = self.positionwise_feedforward(src)
        src = self.ff_layer_norm(src + self.dropout(_src))

        return src


class DecoderLayer(nn.Module):
    """
    This class implements encoder for PositionWise Feed forward layer.

    Arguments
    ---------
    attn_dim : int
        Size of the attention feature.

    Example
    -------
    >>> 

    """

    def __init__(self, hid_dim, n_heads, pf_dim, dropout, device):
        super().__init__()

        self.device = device

        self.self_attn_layer_norm = nn.LayerNorm(hid_dim)
        self.enc_attn_layer_norm = nn.LayerNorm(hid_dim)
        self.ff_layer_norm = nn.LayerNorm(hid_dim)
        self.self_attention = MultiHeadAttentionLayer(hid_dim, n_heads, dropout,
                                                      self.device)
        self.encoder_attention = MultiHeadAttentionLayer(
            hid_dim, n_heads, dropout, self.device)
        self.positionwise_ff = PositionWiseFeedforwardLayer(
            hid_dim, pf_dim, dropout, self.device)
        self.dropout = nn.Dropout(dropout)

    def forward(self, tgt, enc_src, tgt_mask, src_mask):
        """
        tgt shape: [batch, seq-len, hid_dim]
        enc_src shape : [batch, seq-len, hid_dim]
        tgt_mask shape: [batch, 1, 1, seq-len]
        src_mask shape: [batch, 1, 1, seq-len]
        """

        # _tgt shape: [batch, seq-len, hid_dim]
        # _ shape :  [batch, n_heads, seq-len, seq-len]
        _tgt, _ = self.self_attention(tgt, tgt, tgt, tgt_mask)

        # tgt shape: [batch, seq-len, hid_dim]
        tgt = self.self_attn_layer_norm(tgt + self.dropout(_tgt))

        # _tgt shape: [batch, seq-len, hid_dim]
        # attention shape: [batch, n_heads, seq-len, seq-len]
        _tgt, attention = self.encoder_attention(tgt, enc_src, enc_src,
                                                 src_mask)
        # tgt shape:  [batch, seq-len, hid_dim]
        tgt = self.enc_attn_layer_norm(tgt + self.dropout(_tgt))

        # _tgt shape: [batch, seq-len, hid_dim]
        _tgt = self.positionwise_ff(tgt)

        # tgt shape: [batch, seq-len, hid_dim]
        tgt = self.ff_layer_norm(tgt + self.dropout(_tgt))

        return tgt, attention


class Encoder(nn.Module):
    """
    This class implements encoder for seq2seq model.

    Arguments
    ---------
    input_dim: int
        always is  the vocab size.
    hid_dim: int
        The hidden size.
    n_layers: int
           The EncoderLayer layers.
    pf_dim: int
        The position_feedforward dimention

    Example
    -------
    >>> 

    """

    def __init__(self,
                 input_dim,
                 hid_dim,
                 n_layers,
                 n_heads,
                 pf_dim,
                 dropout,
                 device,
                 max_length=64):
        """
        input_dim: vocab_size

        """
        super().__init__()
        self.device = device

        self.tok_emb = nn.Embedding(input_dim, hid_dim)
        self.pos_emb = nn.Embedding(max_length, hid_dim)

        self.layers = nn.ModuleList([
            EncoderLayer(hid_dim, n_heads, pf_dim, dropout, self.device)
            for _ in range(n_layers)
        ])
        self.dropout = nn.Dropout(dropout)
        self.scale = torch.sqrt(torch.FloatTensor([hid_dim])).to(device)

    def forward(self, src, src_mask):
        """
        src shape: [batch, seq-len]
        src_mask shape: [batch, 1, 1, seq-len]

        """
        batch_size = src.shape[0]
        src_len = src.shape[1]
        # pos shape: [seq-len] -> [1, seq-len] -> [batch, seq-len]
        # pos shape: [batch, seq-len]
        pos = torch.arange(0, src_len).unsqueeze(0).repeat(batch_size,
                                                           1).to(self.device)

        # src shape: [batch, seq-len] -> [batch, seq-len, hid_dim]
        # pos_emb shape: [batch, seq-len, hid_dim]

        src = self.dropout((self.tok_emb(src) * self.scale) + self.pos_emb(pos))

        for layer in self.layers:
            src = layer(src, src_mask)
        return src


class Decoder(nn.Module):
    """
    This class implements decoder for seq2seq model.

    Arguments
    ---------
    output_dim : int
        Size of the output dimention.

    Example
    -------
    >>> 

    """

    def __init__(self,
                 output_dim,
                 hid_dim,
                 n_layers,
                 n_heads,
                 pf_dim,
                 dropout,
                 device,
                 max_length=64):
        super().__init__()

        self.device = device

        self.tok_emb = nn.Embedding(output_dim, hid_dim)
        self.pos_emb = nn.Embedding(max_length, hid_dim)

        self.layers = nn.ModuleList([
            DecoderLayer(hid_dim, n_heads, pf_dim, dropout, self.device)
            for _ in range(n_layers)
        ])
        self.fc_out = nn.Linear(hid_dim, output_dim)
        self.dropout = nn.Dropout(dropout)

        self.scale = torch.sqrt(torch.FloatTensor([hid_dim])).to(device)

    def forward(self, tgt, enc_src, tgt_mask, src_mask):
        """
        tgt shape     : [batch, seq-len]
        enc_src shape : [batch, seq-len, hid_dim]
        tgt_mask shape: [batch, 1, 1, seq-len]
        src_mask shape: [batch, 1, 1, seq-len]
        """
        batch_size = tgt.shape[0]
        tgt_len = tgt.shape[1]

        # pos shape: [seq-len] -> [1, seq-len] -> [batch, seq-len]
        pos = torch.arange(0, tgt_len).unsqueeze(0).repeat(batch_size,
                                                           1).to(self.device)
        # tgt shape: [batch, seq-len, hid_dim]
        tgt = self.dropout((self.tok_emb(tgt) * self.scale) + self.pos_emb(pos))

        # tgt shape: [batch, seq-len, hid_dim]
        # attention shape: [batch, n_heads, seq-len, seq-len]
        for layer in self.layers:
            tgt, attention = layer(tgt, enc_src, tgt_mask, src_mask)

        # output shape: [batch, seq-len, output_dim(vocab-size)]
        output = self.fc_out(tgt)

        return output, attention


class Seq2Seq(nn.Module):
    """
    This class implements seq2seq model.

    Arguments
    ---------
    encoder: torch.nn.Module
        The encoder layer
    decoder: torch.nn.Module
        The decoder layer
    src_pad_idx: int
        The id of source.

    Example
    -------
    >>> 

    """

    def __init__(self, encoder, decoder, src_pad_idx, tgt_pad_idx, device):
        super().__init__()
        self.device = device

        self.encoder = encoder
        self.decoder = decoder
        self.src_pad_idx = src_pad_idx
        self.tgt_pad_idx = tgt_pad_idx

    def make_src_mask(self, src):
        """
        src shape: [batch, seq-len]

        """
        # src_mask shape: [batch, 1, 1, seq-len]
        src_mask = (src != self.src_pad_idx).unsqueeze(1).unsqueeze(2).to(
            self.device)

        return src_mask

    def make_tgt_mask(self, tgt):
        """
        tgt shape: [batch, seq-len]
        """
        # tgt_pad_mask shape: [batch, 1, 1, seq-len]
        tgt_pad_mask = (tgt != self.tgt_pad_idx).unsqueeze(1).unsqueeze(2).to(
            self.device)
        tgt_len = tgt.shape[1]

        # tgt_sub_mask shape: [seq-len, seq-len]
        tgt_sub_mask = torch.tril(torch.ones(
            (tgt_len, tgt_len))).bool().to(self.device)

        # tgt_mask shape: [batch, 1, 1, seq-len]
        tgt_mask = tgt_pad_mask & tgt_sub_mask

        return tgt_mask

    def forward(self, src, tgt):
        """
        src shape: [batch, seq-len]
        tgt shape: [batch, seq-len]

        """
        # src_mask shape: [batch, 1, 1, seq-len]
        src_mask = self.make_src_mask(src)

        # enc_src shape: [batch, seq-len, hid_dim]
        enc_src = self.encoder(src, src_mask)

        # tgt_mask shape: [batch, 1, 1, seq-len]
        tgt_mask = self.make_tgt_mask(tgt)

        # output shape: [batch, seq-len, output-dim]
        # attention shape: [batch, n_heads, seq-len, seq-len]
        output, attention = self.decoder(tgt, enc_src, tgt_mask, src_mask)

        return output, attention
