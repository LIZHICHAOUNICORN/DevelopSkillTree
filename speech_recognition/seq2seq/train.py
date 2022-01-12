import torch
import torch.nn as nn
import torch.optim as optim
import torch.nn.functional as F
import logging

from models import Encoder, Decoder, Seq2Seq
from dataio import get_batch

FORMAT = '%(asctime)s %(filename)s %(funcName)s %(lineno)d %(message)s'
logging.basicConfig(level=logging.INFO, format=FORMAT)

# device = torch.device("cuda" if torch.cudda.is_available() else "cpu")

device = torch.device("cpu")

VOCAB_SIZE = 27
ENC_EMB_DIM = 128
DEC_EMB_DIM = 128
HID_DIM = 256
N_LAYERS = 2
ENC_DROPOUT = 0.5
DEC_DROPOUT = 0.5
SEQ_LEN = 32


def compute_loss(logits, target, criterion):
    """
    logits shape: [seq-len, batch-size, output_dim]
    target shape: [batch-size, seq-len]

    """

    loss = criterion(logits, target)

    return loss


def train_one_step(model, optimizer, enc_x, dec_x, y, criterion):
    model.train()

    optimizer.zero_grad()
    # logits shape: [batch-size, seqlen]
    logits = model(enc_x, dec_x)

    output_dim = logits.shape[-1]
    logits = logits[1:].view(-1, output_dim)
    y = y[1:].contiguous().view(-1)

    loss = compute_loss(logits, y, criterion)
    loss.backward()
    optimizer.step()
    return loss


def decode_logits(logits, batch_size, seq_len):
    result = []
    for batch in range(batch_size):
        ret = []
        for seq in range(seq_len):
            ret.append(logits[batch][seq].argmax().item())
        result.append(ret)

    hyps = []
    for ret in result:
        hyp = ''
        for r in ret:
            hyp += chr(r+ord('A')-1)
        hyps.append(hyp)

    logging.info("decode: {}".format(hyps))


def decode(hidden, cell, seq_len):
    b_sz = hidden.shape[1]
    vocab_size = model.decoder.output_dim

    collect = torch.zeros(seq_len, b_sz, vocab_size).to(device)
    cur_token = torch.zeros(size=[b_sz], dtype=torch.int32)
    # tokens = torch.zeros(b_sz, seq_len)
    tokens = []
    for i in range(seq_len):
        cur_token, output, hidden, cell = model.get_next_token(cur_token, hidden, cell)
        if i != 0:
            collect[i] = output
        # tokens[i] = cur_token
        tokens.append(cur_token)

    ids = []
    for exp in tokens:
        for idx in exp.tolist():
            ids.append(idx)

    # out = [''.join([chr(idx + ord('A') - 1) for idx in exp.tolist()]) for exp in tokens]
    result = []
    for offset in range(b_sz):
        ret = []
        cur = 0
        for i in range(seq_len):
            ret.append(ids[cur+offset])
            cur += b_sz
        result.append(ret)
    hyps = []
    for ret in result:
        hyp = ''
        for r in ret:
            hyp += chr(r+ord('A')-1)
        hyps.append(hyp)

    logging.info("decode: {}".format(hyps))
    return collect


def evaluate(model, seqlen, criterion):
    model.eval()

    with torch.no_grad():
        batch_size = 2
        batched_samples, enc_x, dec_x, y = get_batch(batch_size, seqlen)
        y = y.transpose(0, 1)
        logits = model(enc_x, dec_x, 0)
        decode_logits(logits.transpose(0,1), batch_size, seqlen)

        # hidden, cell = model.encoder(enc_x)
        # logits = decode(hidden, cell, seqlen)
        label = [''.join([chr(idx + ord('A') - 1) for idx in exp]) for exp in y.transpose(0,1).tolist()]
        logging.info("label: \t  {}".format(label))
        logging.info("input: \t  {}".format(batched_samples))


        output_dim = model.decoder.output_dim
        logits = logits[1:].view(-1, output_dim)
        y = y[1:].contiguous().view(-1)

        loss = compute_loss(logits, y, criterion)
        logging.info("eval: {}".format(loss.item()))


def train(model, optimizer, seqlen, criterion):
    loss = 0.0
    accuracy = 0.0


    for step in range(1, 300000):
        """
        batched_samples shape: [batch-size]
        enc_x shape: [batch-size, seqlen]
        dec_x shape: [batch-size, seqlen]
        y shape: [batch-size, seqlen]

        """
        batched_samples, enc_x, dec_x, y = get_batch(32, seqlen)
        # loss shape:
        y = y.transpose(0, 1)
        loss = train_one_step(model, optimizer, enc_x, dec_x, y, criterion)
        if step % 1000 == 0:
            logging.info("step: {}, loss: {}".format(step, loss.item()))
            evaluate(model, seqlen, criterion)

    return loss


def count_parameters(model):
    return sum(p.numel() for p in model.parameters() if p.requires_grad)


def init_weights(model):
    for name, param in model.named_parameters():
        nn.init.uniform_(param.data, -0.08, 0.08)


if __name__ == "__main__":
    enc = Encoder(VOCAB_SIZE, ENC_EMB_DIM, HID_DIM, N_LAYERS, ENC_DROPOUT)
    dec = Decoder(VOCAB_SIZE, DEC_EMB_DIM, HID_DIM, N_LAYERS, DEC_DROPOUT)

    model = Seq2Seq(enc, dec, device).to(device)
    criterion = nn.CrossEntropyLoss()

    model.apply(init_weights)
    logging.debug(model)

    param_sum = count_parameters(model)
    logging.info("model parameters: {}".format(param_sum))

    optimizer = optim.Adam(model.parameters(), lr=0.0005)

    train(model, optimizer, SEQ_LEN, criterion)
